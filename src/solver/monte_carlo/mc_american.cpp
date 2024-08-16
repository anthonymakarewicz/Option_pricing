#include "solver/monte_carlo/mc_american.h"
#include <random/number_generator/random_generator.h>
#include "Eigen/Dense"

namespace OptionPricer {

    AmericanMCPricer::AmericanMCPricer(std::shared_ptr<AmericanOption> option,
                                       std::shared_ptr<IMarketData> marketData,
                                       std::shared_ptr<StockModel> stockModel,
                                       std::shared_ptr<NumberGenerator> generator,
                                       std::shared_ptr<BasisFunctionStrategy> basisFunctionStrategy,
                                       std::shared_ptr<RegressionStrategy> regressionStrategy,
                                       const unsigned int& steps)
    : PathDependentMCPricer(std::move(marketData),std::move(stockModel),
        std::move(generator), steps), option_(std::move(option)),
    basisFunctionStrategy_(std::move(basisFunctionStrategy)),
    regressionStrategy_(std::move(regressionStrategy)) {}

    double AmericanMCPricer::calculate_price(const unsigned long &N) const {
        const double dt = option_->getT() / static_cast<double>(steps_);
        const double discountFactor = exp(-marketData_->getR() * dt);

        if (std::dynamic_pointer_cast<RandomNumberGenerator>(generator_)) {
            return brownianBridgePrice(N, dt, discountFactor);
        }

        return standardPrice(N, dt, discountFactor);
    }

    double AmericanMCPricer::standardPrice(const unsigned long &N,
                                           const double &dt,
                                           const double &discountFactor) const {
       /* This algorithm uses the Least Square Monte Carlo (LSMC) method as described in
        * Longstaff and Schwartz (2001) for pricing American options.
        */
        const double S = marketData_->getStockData(option_->getID())->getPrice();
        Eigen::MatrixXd paths(N, steps_+1);
        paths.col(0).setConstant(S);

        // Step 1: Simulate paths
        for (int i = 0; i < N; ++i) {
            for (int j = 1; j <= steps_; ++j) {
                double z = generator_->generate(j - 1);
                paths(i, j) = paths(i, j - 1) * stockModel_->simulateStepPrice(dt, z);
            }
        }

        // Step 2: Initialize americanPrices with the payoff at maturity
        Eigen::VectorXd americanPrices = paths.col(steps_).unaryExpr([this](const double& path){
            return option_->payoff(path);
        });

        // Step 3: Perform backward induction
        for (int j = static_cast<int>(steps_) - 1; j >= 1; --j) {
            std::vector<double> inTheMoneyPaths, discountedCashFlows;
            std::vector<bool> isInTheMoney;

            for (int i = 0; i < N; ++i) {
                const double exerciseValue = option_->payoff(paths(i, j));

                // Collect In-The-Money paths
                if (exerciseValue > 0.0) {
                    inTheMoneyPaths.push_back(paths(i, j));
                    discountedCashFlows.push_back(americanPrices(i) * discountFactor);
                    isInTheMoney.push_back(true);
                } else {
                    isInTheMoney.push_back(false);
                }
            }

            // Step 4: Regression to estimate continuation values with basis functions
            if (!inTheMoneyPaths.empty()) {
                Eigen::VectorXd vInTheMoneyPaths = Eigen::Map<Eigen::VectorXd>(inTheMoneyPaths.data(),
                                                                               inTheMoneyPaths.size());
                Eigen::VectorXd vDiscountedCashFlows = Eigen::Map<Eigen::VectorXd>(discountedCashFlows.data(),
                                                                                   discountedCashFlows.size());

                const Eigen::MatrixXd inTheMoneyBases = basisFunctionStrategy_->generate(vInTheMoneyPaths);
                const Eigen::VectorXd coeffs = regressionStrategy_->solve(inTheMoneyBases, vDiscountedCashFlows);

                // Step 5: Determine whether to exercise or continue
                int idxITM = 0;
                for (int i = 0; i < N; ++i) {
                    if (isInTheMoney[i]) {
                        const double exerciseValue = option_->payoff(paths(i, j));
                        const double continuationValue = inTheMoneyBases.row(idxITM) * coeffs;
                        idxITM++;
                        if (exerciseValue > continuationValue) {
                            americanPrices(i) = exerciseValue;
                        } else {
                            americanPrices(i) *= discountFactor;
                        }
                    } else {
                        americanPrices(i) *= discountFactor;
                    }
                }
            }
        }

        // Step 6: Compute the option price as the expected discounted payoffs
        return americanPrices.mean() * discountFactor;
    }

    double AmericanMCPricer::brownianBridgePrice(const unsigned long &N,
                                                 const double &dt,
                                                 const double &discountFactor) const{
        /* This algorithm is an extension of the Longstaff and Schwartz (2001)
         * which introduce a brownian bridge to store only the simulated paths for 1 time step
         * instead thus reducing memory complexity from O(N x m) to O(N) where N is the number of
         * simulations and m the number of steps.
         */
        const double S = marketData_->getStockData(option_->getID())->getPrice();
        const double sigma = marketData_->getStockData(option_->getID())->getSigma();

        // Step 1: Simulate paths at maturity
        Eigen::VectorXd paths(N);
        for (int i = 0; i < N; ++i) {
            const double z = generator_->generate(0); // For each path generate a steps_ dimensional point
            paths(i) = stockModel_->simulatePriceAtMaturity(option_->getT(), z);
        }

        // Step 2: Initialize americanPrices with the payoff at maturity
        Eigen::VectorXd americanPrices = paths.unaryExpr([this](const double& path) {
            return option_->payoff(path);
        });

        // Step 3: Perform backward induction
        for (int j = static_cast<int>(steps_) - 1; j > 0; --j) {
            std::vector<double> inTheMoneyPaths, discountedCashFlows;
            std::vector<bool> isInTheMoney;

            // Generate stock prices backward using Brownian Bridge
            for (int i = 0; i < N; ++i) {
                const double t_j = static_cast<double>(j) * dt;      // Time at current step
                const double t_jp1 = static_cast<double>(j+1) * dt; // Time at the next step
                const double X_next = log(paths(i) / S);
                const double z = generator_->generate(static_cast<int>(steps_) - j);

                // Use the Brownian Bridge interpolation formula
                const double X_curr = (t_j/t_jp1) * X_next + sqrt(t_j*dt/t_jp1) * sigma * z;
                paths(i) = S * exp(X_curr);
                const double exerciseValue = option_->payoff(paths(i));

                // Collect In-The-Money paths
                if (exerciseValue > 0.0) {
                    inTheMoneyPaths.push_back(paths(i));
                    discountedCashFlows.push_back(americanPrices(i) * discountFactor);
                    isInTheMoney.push_back(true);
                } else {
                    isInTheMoney.push_back(false);
                }
            }

            // Step 4: Regression to estimate continuation values with basis functions
            if (!inTheMoneyPaths.empty()) {
                Eigen::VectorXd vInTheMoneyPaths = Eigen::Map<Eigen::VectorXd>(inTheMoneyPaths.data(),
                                                                               inTheMoneyPaths.size());
                Eigen::VectorXd vDiscountedCashFlows = Eigen::Map<Eigen::VectorXd>(discountedCashFlows.data(),
                                                                                   discountedCashFlows.size());

                const Eigen::MatrixXd inTheMoneyBases = basisFunctionStrategy_->generate(vInTheMoneyPaths);
                const Eigen::VectorXd coeffs = regressionStrategy_->solve(inTheMoneyBases, vDiscountedCashFlows);

                // Step 5: Determine whether to exercise or continue
                int idxITM = 0;
                for (int i = 0; i < N; ++i) {
                    if (isInTheMoney[i]) {
                        const double exerciseValue = option_->payoff(paths(i));
                        const double continuationValue = coeffs.dot(inTheMoneyBases.row(idxITM));
                        ++idxITM;
                        if (exerciseValue > continuationValue) {
                            americanPrices(i) = exerciseValue;
                        } else {
                            americanPrices(i) *= discountFactor;
                        }
                    } else {
                        americanPrices(i) *= discountFactor;
                    }
                }
            }
        }

        // Step 6: Compute the option price as the expected discounted payoffs
        return americanPrices.mean() * discountFactor;
    }

}
