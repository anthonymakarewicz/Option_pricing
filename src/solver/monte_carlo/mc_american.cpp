#include "solver/monte_carlo/mc_american.h"
#include "Eigen/Dense"

namespace OptionPricer {

    AmericanMCPricer::AmericanMCPricer(std::shared_ptr<AmericanOption> option,
                                       std::shared_ptr<IMarketData> marketData,
                                       std::shared_ptr<StockModel> stockModel,
                                       std::shared_ptr<NumberGenerarator> generator,
                                       std::shared_ptr<BasisFunctionStrategy> basisFunctionStrategy,
                                       std::shared_ptr<RegressionStrategy> regressionStrategy,
                                       const unsigned int& steps)
    : PathDependentMCPricer(std::move(marketData),std::move(stockModel),
        std::move(generator), steps), option_(std::move(option)),
    basisFunctionStrategy_(std::move(basisFunctionStrategy)),
    regressionStrategy_(std::move(regressionStrategy)) {}

    double AmericanMCPricer::calculate_price(const unsigned long &N) const {
          /* This algorithm uses the Least Square Monte Carlo (LSMC) method as described in
             * Longstaff and Schwartz (2001) for pricing American options.
             */
            const double dt = option_->getT() / static_cast<double>(steps_);
            Eigen::MatrixXd paths(N, steps_ + 1);

            // Step 1: Simulate paths
            for (int i = 0; i < N; ++i) {
                paths(i, 0) = marketData_->getStockData(option_->getID())->getPrice();
                for (int j = 1; j <= steps_; ++j) {
                    double z = generator_->generate(j - 1);
                    paths(i, j) = paths(i, j - 1) * stockModel_->simulateStepPrice(dt, z);
                }
            }

            // Step 2: Initialize americanPrices with the payoff at maturity
            Eigen::VectorXd americanPrices(N);
            for (int i = 0; i < N; ++i) {
                americanPrices(i) = option_->payoff(paths(i, steps_));
            }

            // Step 3: Perform backward induction
            for (int step = static_cast<int>(steps_) - 1; step >= 0; --step) {
                std::vector<double> inTheMoneyPaths, discountedCashFlows;
                std::vector<bool> isInTheMoney;
                // Collect In-The-Money paths
                for (int i = 0; i < N; ++i) {
                    const double exerciseValue = option_->payoff(paths(i, step));
                    if (exerciseValue > 0.0) {
                        inTheMoneyPaths.push_back(paths(i, step)); //
                        discountedCashFlows.push_back(americanPrices(i) * exp(-marketData_->getR() * dt));
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

                    // Generate basis functions for all paths at the current step
                    //const Eigen::MatrixXd allPathsBases = basisFunctionStrategy_->generate(paths.col(step));
                    int idxITM = 0;
                    // Step 5: Determine whether to exercise or continue
                    for (int i = 0; i < N; ++i) {
                        if (isInTheMoney[i]) {
                            const double exerciseValue = option_->payoff(paths(i, step));
                            const double continuationValue = inTheMoneyBases.row(idxITM) * coeffs;
                            idxITM++;
                            if (exerciseValue > continuationValue) {
                                americanPrices(i) = exerciseValue;
                            } else {
                                americanPrices(i) *= exp(-marketData_->getR() * dt);
                            }
                        } else {
                            americanPrices(i) *= exp(-marketData_->getR() * dt);
                        }
                    }
                }
            }

            // Step 6: Compute the option price as the expected discounted payoffs
            return (americanPrices.sum() / static_cast<double>(N));
        }

}