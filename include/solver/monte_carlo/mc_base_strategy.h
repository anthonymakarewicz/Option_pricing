#ifndef MC_BASE_STRATEGY_H
#define MC_BASE_STRATEGY_H

#include <option/path_dependent/lookback_option.h>

#include "option/path_dependent/asian_option.h"
#include "option/path_dependent/barrier_option.h"
#include "option/path_dependent/american_option.h"
#include "option/base_option.h"
#include "option/single_path/base_single_path_option.h"
#include "option/path_dependent/base_path_dependent_option.h"
#include "solver/monte_carlo/stock_price_model.h"
#include "solver/monte_carlo/generator.h"
#include "option/path_dependent/factory_american_option.h"
#include <Eigen/Dense>


namespace OptionPricer {
    // Alternatively we would have inherit a IMCStrategy and for most of the option taking a shared_ptr<Option>
    // by inheriting MCStrategy, but for barrier options could have inherited diretcly from IMCStrategy and defining
    // its own entire code by using dynamic cast instead
    class MCStrategy {
    public:
        MCStrategy(std::shared_ptr<StockPriceModel> stockModel,
                   std::shared_ptr<NumberGenerarator> generator, std::shared_ptr<IMarketData> marketData)
        : stockModel_(std::move(stockModel)), generator_(std::move(generator)),
        marketData_(std::move(marketData)) {}

        virtual ~MCStrategy() = default;

        [[nodiscard]] virtual double calculate_price(const unsigned long& N) const = 0;

    protected:
        std::shared_ptr<StockPriceModel> stockModel_;
        std::shared_ptr<NumberGenerarator> generator_;
        std::shared_ptr<IMarketData> marketData_;
    };


    class SinglePathMCStrategy final: public MCStrategy {
    public:
        SinglePathMCStrategy(std::shared_ptr<Option> option, std::shared_ptr<StockPriceModel> stockModel,
                             std::shared_ptr<NumberGenerarator> generator, std::shared_ptr<IMarketData> marketData)
            : MCStrategy(std::move(stockModel), std::move(generator),
                std::move(marketData)) {
            if (auto optionSinglePath = std::dynamic_pointer_cast<SinglePathOption>(option)) {
                option_ = std::move(optionSinglePath);
            }
            else {
                throw std::invalid_argument("option should be a SinglePath");
            }

            if (const auto generatorQR = std::dynamic_pointer_cast<QRNGenerator>(generator_)) {
                if (generatorQR->getDim() != 1) {
                    throw std::invalid_argument("For SinglePath options, the dim parameter of QRNGenerator "
                                                  "must be 1");
                }
            }
        }

        ~SinglePathMCStrategy() override = default;

        [[nodiscard]] double calculate_price(const unsigned long& N) const override {
            double sumPayoff = 0.0;

            for (int i = 0; i < N; ++i) {
                const double z = generator_->generate(0);
                double S_T = stockModel_->simulatePriceAtMaturity(option_->getT(), z);
                sumPayoff += option_->payoff(S_T);
            }

            return (sumPayoff / static_cast<double>(N)) * exp(- marketData_->getR()*option_->getT());
        }

    private:
        std::shared_ptr<SinglePathOption> option_;
    };

    class PathDependentMCStrategy : public MCStrategy {
    public:
        PathDependentMCStrategy(std::shared_ptr<StockPriceModel> stockModel,std::shared_ptr<NumberGenerarator> generator,
            std::shared_ptr<IMarketData> marketData, const unsigned int& steps)
        : MCStrategy(std::move(stockModel), std::move(generator),std::move(marketData)),
          steps_(steps) {
            if (const auto generatorQR = std::dynamic_pointer_cast<QRNGenerator>(generator_)) {
                if (generatorQR->getDim() != steps_) {
                    steps_ = static_cast<int>(generatorQR->getDim());
                    std::cerr << "For PathDependent options, the steps parameter ";
                    std::cerr << "must be equal to the dim of derived QRNGenerator." << "\n";
                    std::cerr << "steps is thus set to " << generatorQR->getDim() << "\n";
                }
            }
        }

    protected:
        unsigned int steps_;
    };

    class AsianMCStrategy : public PathDependentMCStrategy {
    public:
        AsianMCStrategy(std::shared_ptr<Option> option, std::shared_ptr<StockPriceModel> stockModel,
                        std::shared_ptr<NumberGenerarator> generator, std::shared_ptr<IMarketData> marketData,
                        const unsigned int& steps)
            : PathDependentMCStrategy(std::move(stockModel), std::move(generator),
                std::move(marketData), steps) {
            if (auto optionSinglePath = std::dynamic_pointer_cast<AsianOption>(option)) {
                option_ = std::move(optionSinglePath);
            }
            else {
                throw std::invalid_argument("option should be a Asian");
            }
        }

        [[nodiscard]] double calculate_price(const unsigned long& N) const override {
            double sumPayoff = 0.0;
            const double dt = option_->getT() / static_cast<double>(steps_);

            for (int i = 0; i < N; ++i) {
                double S_t = marketData_->getStockData(option_->getID())->getPrice();
                double sumPrices = 0.0;

                for (int step = 0; step < steps_; ++step) {
                    double z = generator_->generate(step);
                    S_t *= stockModel_->simulateStepPrice(dt, z);
                    sumPrices += computeSumPrices(S_t);
                    //std::cout << "Period: " << step << ", Price: " << S_t << "\n";
                }

                const double averagePrice = computeAveragePrice(sumPrices);
                sumPayoff += option_->payoff(averagePrice);
            }

            return (sumPayoff / static_cast<double>(N)) * exp(- marketData_->getR()*option_->getT());
        }

    protected:
        virtual double computeSumPrices(const double& S_t) const = 0;
        virtual double computeAveragePrice(const double& averagePrice) const = 0;

        std::shared_ptr<AsianOption> option_;
    };


    class ArithmeticAsianMCStrategy final: public AsianMCStrategy {
    public:
        using AsianMCStrategy::AsianMCStrategy;

    private:
        double computeSumPrices(const double& S_t) const override {
            return S_t;
        }

        double computeAveragePrice(const double& averagePrice) const override {
            return averagePrice / static_cast<double>(steps_);
        }
    };


    class GeometricAsianMCStrategy final: public AsianMCStrategy {
    public:
        using AsianMCStrategy::AsianMCStrategy;

    private:
        double computeSumPrices(const double& S_t) const override {
            return log(S_t);
        }

        double computeAveragePrice(const double& averagePrice) const override {
            return exp(averagePrice / static_cast<double>(steps_));
        }
    };


    class BarrierMCStrategy : public PathDependentMCStrategy {
    public:
        BarrierMCStrategy(std::shared_ptr<Option> option, std::shared_ptr<StockPriceModel> stockModel,
                          std::shared_ptr<NumberGenerarator> generator, std::shared_ptr<IMarketData> marketData,
                          const unsigned int& steps)
            : PathDependentMCStrategy(std::move(stockModel), std::move(generator),
                std::move(marketData), steps) {
            if (auto optionBarrier = std::dynamic_pointer_cast<BarrierOption>(option)) {
                option_ = std::move(optionBarrier);
            }
            else {
                throw std::invalid_argument("option should be a BarrierOption");
            }
        }

        [[nodiscard]] double calculate_price(const unsigned long& N) const override {
            double sumPayoff = 0.0;
            const double dt = option_->getT() / static_cast<double>(steps_);

            for (int i = 0; i < N; ++i) {
                double S_t = marketData_->getStockData(option_->getID())->getPrice();
                bool hasCrossed = false;
                //std::cout << "Intial Stock Price: " << S_t << "\n";

                for (int step = 0; step < steps_; ++step) {
                    double z = generator_->generate(step);
                    S_t *= stockModel_->simulateStepPrice(dt, z);

                    //std::cout << "Period: " << step << ", Price: " << S_t << "\n";

                    if (checkHasCrossed(S_t, hasCrossed)) {
                        break;
                    }
                }
                //std::cout << "Final Stock Price: " << S_t << "\n";
                //std::cout << "Payoff: " << computePayoff(S_t, hasCrossed) << "\n";
                sumPayoff += computePayoff(S_t, hasCrossed);
            }

            return (sumPayoff / static_cast<double>(N)) * exp(-marketData_->getR()*option_->getT());
        }

    protected:
        virtual bool checkHasCrossed(const double& S_t, bool& hasCrossed) const = 0;
        virtual double computePayoff(const double& S_t, const bool& hasCrossed) const = 0;

        std::shared_ptr<BarrierOption> option_;
    };


    class KnockInMCStrategy final : public BarrierMCStrategy {
    public:
        using BarrierMCStrategy::BarrierMCStrategy;

    protected:
        bool checkHasCrossed(const double& S_t, bool& hasCrossed) const override {
            if (option_->isActive(S_t)) {
                //std::cout << "Barrier Crossed" << "\n";
                hasCrossed = true;
            }
            return false; // Never exit early for Knock-In
        }

        double computePayoff(const double& S_t, const bool& hasCrossed) const override {
            return hasCrossed ? option_->payoff(S_t) : 0.0;
        }
    };


    class KnockOutMCStrategy final : public BarrierMCStrategy {
    public:
        using BarrierMCStrategy::BarrierMCStrategy;

    protected:
        bool checkHasCrossed(const double& S_t, bool& hasCrossed) const override {
            if (!option_->isActive(S_t)) {
                hasCrossed = true;
                //std::cout << "Barrier Crossed" << "\n";
                return true; // Exit the loop early
            }
            return false; // Continue the loop
        }

        double computePayoff(const double& S_t, const bool& hasCrossed) const override {
            return hasCrossed ? 0.0 : option_->payoff(S_t);
        }
    };


    class LookbackMCStrategy : public PathDependentMCStrategy {
    public:
        using PathDependentMCStrategy::PathDependentMCStrategy;

        [[nodiscard]] double calculate_price(const unsigned long& N) const override {
            double sumPayoff = 0.0;
            const double dt = option_->getT() / static_cast<double>(steps_);

            for (int i = 0; i < N; ++i) {
                double S_t = marketData_->getStockData(option_->getID())->getPrice();
                double S_min = S_t;
                double S_max = S_t;

                for (int step = 0; step < steps_; ++step) {
                    double z = generator_->generate(step);
                    S_t *= stockModel_->simulateStepPrice(dt, z);

                    // Track min and max price during the simulation
                    S_min = std::min(S_min, S_t);
                    S_max = std::max(S_max, S_t);

                    //std::cout << "Period: " << step << ", Price: " << S_t << "\n";
                }
                //std::cout << "S_min: " << S_min << ", S_max: " << S_max << "\n";
                //std::cout << "Final Payoff: " << computePayoff(S_t, S_min, S_max) << "\n";

                // Calculate the payoff based on min and max prices
                sumPayoff += computePayoff(S_t, S_min, S_max);

            }

            return (sumPayoff / static_cast<double>(N)) * exp(-marketData_->getR() * option_->getT());
        }

    protected:
        // Pure virtual method to calculate the payoff based on S_t, S_min, and S_max
        virtual double computePayoff(const double& S_t, const double& S_min, const double& S_max) const = 0;

        std::shared_ptr<LookbackOption> option_;
    };


    class FloatingStrikeLookbackMCStrategy : public LookbackMCStrategy {
    public:
        FloatingStrikeLookbackMCStrategy(std::shared_ptr<Option> option, std::shared_ptr<StockPriceModel> stockModel,
                                         std::shared_ptr<NumberGenerarator> generator, std::shared_ptr<IMarketData> marketData,
                                         const unsigned int& steps)
            : LookbackMCStrategy(std::move(stockModel), std::move(generator),
                                 std::move(marketData), steps) {
            if (auto optionLookback = std::dynamic_pointer_cast<FloatingStrikeLookbackOption>(option)) {
                option_ = std::move(optionLookback);
            }
            else {
                throw std::invalid_argument("option should be a FloatingStrikeLookbackOption");
            }
        }

    private:
        // Implement the logic for Floating Strike Lookback Option
        double computePayoff(const double& S_t, const double& S_min, const double& S_max) const override {
            // Choose min for call and max for put
            return option_->getPayoff().getPayoffType() == PayoffType::Call
                   ? option_->payoff(S_t, S_min)  // max(S_T - S_min, 0)
                   : option_->payoff(S_t, S_max); // max(S_max - S_T, 0)
        }
    };

    class FixedStrikeLookbackMCStrategy : public LookbackMCStrategy {
    public:
        FixedStrikeLookbackMCStrategy(std::shared_ptr<Option> option, std::shared_ptr<StockPriceModel> stockModel,
                                      std::shared_ptr<NumberGenerarator> generator, std::shared_ptr<IMarketData> marketData,
                                      const unsigned int& steps)
            : LookbackMCStrategy(std::move(stockModel), std::move(generator),
                                 std::move(marketData), steps) {
            if (auto optionLookback = std::dynamic_pointer_cast<FixedStrikeLookbackOption>(option)) {
                option_ = std::move(optionLookback);
            }
            else {
                throw std::invalid_argument("option should be a FixedStrikeLookbackOption");
            }
        }

    private:
        // Implement the logic for Fixed Strike Lookback Option
        double computePayoff(const double& S_t, const double& S_min, const double& S_max) const override {
            return option_->getPayoff().getPayoffType() == PayoffType::Call
                   ? option_->payoff(S_max)  // max(S_max - K, 0)
                   : option_->payoff(S_min); // max(K - S_min, 0)
        }
    };


    class AmericanMCStrategy : public PathDependentMCStrategy {
    public:
        AmericanMCStrategy(std::shared_ptr<Option> option, std::shared_ptr<StockPriceModel> stockModel,
                           std::shared_ptr<NumberGenerarator> generator, std::shared_ptr<IMarketData> marketData,
                           const unsigned int& steps)
            : PathDependentMCStrategy(std::move(stockModel), std::move(generator), std::move(marketData), steps),
              option_(std::dynamic_pointer_cast<AmericanOption>(option)) {
            if (!option_) {
                throw std::invalid_argument("Option must be an American option.");
            }
        }

        double calculate_price(const unsigned long& N) const override {
            /* This algorithm uses the Least Square Monte Carlo (LSMC) method as described in
             * Longstaff and Schwartz (2001) for pricing American options.
             */

            double sumPayoff = 0.0;
            double dt = option_->getT() / static_cast<double>(steps_);
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

                // Collect in-the-money paths
                for (unsigned long i = 0; i < N; ++i) {
                    double exerciseValue = option_->payoff(paths[i][step]);
                    if (exerciseValue > 0.0) {
                        X.push_back(paths[i][step]); //
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

    private:
        std::shared_ptr<AmericanOption> option_;
};

}




#endif //MC_BASE_STRATEGY_H
