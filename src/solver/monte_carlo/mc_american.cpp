#include "solver/monte_carlo/mc_american.h"
#include "Eigen/Dense"

namespace OptionPricer {

    AmericanMCPricer::AmericanMCPricer(std::shared_ptr<AmericanOption> option,
                                       std::shared_ptr<IMarketData> marketData,
                                       std::shared_ptr<StockPriceModel> stockModel,
                                       std::shared_ptr<NumberGenerarator> generator,
                                       const unsigned int& steps)
    : PathDependentMCPricer(std::move(marketData),std::move(stockModel),
        std::move(generator), steps), option_(std::move(option)) {}

    double AmericanMCPricer::calculate_price(const unsigned long &N) const {
            /* This algorithm uses the Least Square Monte Carlo (LSMC) method as described in
             * Longstaff and Schwartz (2001) for pricing American options.
             */

            double sumPayoff = 0.0;
            const double dt = option_->getT() / static_cast<double>(steps_);
            std::vector<std::vector<double>> paths(N, std::vector<double>(steps_ + 1));

            // Step 1: Simulate paths
            for (unsigned long i = 0; i < N; ++i) {
                paths[i][0] = marketData_->getStockData(option_->getID())->getPrice();
                for (unsigned int j = 1; j <= steps_; ++j) {
                    double z = generator_->generate(j - 1);
                    paths[i][j] = paths[i][j - 1] * stockModel_->simulateStepPrice(dt, z);
                }
            }

            // Step 2: Initialize cash flows at maturity
            Eigen::VectorXd cashFlows(N);
            for (unsigned long i = 0; i < N; ++i) {
                cashFlows(i) = option_->payoff(paths[i].back());
            }

            // Step 3: Perform backward induction
            for (int step = steps_ - 1; step >= 0; --step) {
                std::vector<double> X, Y;

                // Collect In-The-Money paths
                for (unsigned long i = 0; i < N; ++i) {
                    if (const double exerciseValue = option_->payoff(paths[i][step]); exerciseValue > 0.0) {
                        X.push_back(paths[i][step]);
                        Y.push_back(cashFlows(i) * exp(-marketData_->getR() * dt));
                    }
                }

                // Step 4: Least squares regression to estimate continuation values
                if (!X.empty()) {
                    Eigen::VectorXd vX = Eigen::Map<Eigen::VectorXd, Eigen::Unaligned>(X.data(), X.size());
                    Eigen::MatrixXd A(X.size(), 3);           // 3 polynomial basis functions:
                    A.col(0) = Eigen::VectorXd::Ones(X.size()); // f1(x) = 1
                    A.col(1) = vX;                              // f2(x) = x
                    A.col(2) = vX.cwiseProduct(vX);             // f3(x) = x^2
                    Eigen::VectorXd vY = Eigen::Map<Eigen::VectorXd, Eigen::Unaligned>(Y.data(), Y.size());
                    Eigen::VectorXd coeffs = A.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(vY);

                    // Step 5: Determine whether to exercise or continue
                    for (unsigned long i = 0; i < N; ++i) {
                        double continuationValue = coeffs(0) + coeffs(1) * paths[i][step] +
                            coeffs(2) * paths[i][step] * paths[i][step];
                        double exerciseValue = option_->payoff(paths[i][step]);

                        if (exerciseValue > continuationValue) {
                            cashFlows(i) = exerciseValue;
                        } else {
                            cashFlows(i) *= exp(-marketData_->getR() * dt);
                        }
                    }
                }
            }

            // Step 6: Compute the option price as the expected discounted payoffs
            sumPayoff = cashFlows.sum();
            return (sumPayoff / static_cast<double>(N));
        }

}
