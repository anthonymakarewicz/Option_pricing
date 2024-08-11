#ifndef MC_BASE_STRATEGY_H
#define MC_BASE_STRATEGY_H

#include "option/path_dependent/asian_option.h"
#include "option/path_dependent/barrier_option.h"

#include "option/base_option.h"
#include "option/single_path/base_single_path_option.h"
#include "option/path_dependent/base_path_dependent_option.h"
#include "solver/monte_carlo/stock_price_model.h"
#include "solver/monte_carlo/generator.h"


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

            return (sumPayoff / static_cast<double>(N)) * exp(- marketData_->getR()*option_->getT());
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
}




#endif //MC_BASE_STRATEGY_H
