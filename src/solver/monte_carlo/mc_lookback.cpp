#include "solver/monte_carlo/mc_lookback.h"

namespace OptionPricer {

    // Base Lookback
    LookbackMCPricer::LookbackMCPricer(std::shared_ptr<LookbackOption> option,
                                       std::shared_ptr<IMarketData> marketData,
                                       std::shared_ptr<StockPriceModel> stockModel,
                                       std::shared_ptr<NumberGenerarator> generator,
                                       const unsigned int& steps)
    : PathDependentMCPricer(std::move(marketData),std::move(stockModel),
        std::move(generator), steps), option_(std::move(option)) {}

    double LookbackMCPricer::calculate_price(const unsigned long &N) const {
        double sumPayoff = 0.0;
        const double dt = option_->getT() / static_cast<double>(steps_);

        for (int i = 0; i < N; ++i) {
            double S_t = marketData_->getStockData(option_->getID())->getPrice();
            double S_min = S_t;
            double S_max = S_t;

            for (int step = 0; step < steps_; ++step) {
                double z = generator_->generate(step);
                S_t *= stockModel_->simulateStepPrice(dt, z);

                S_min = std::min(S_min, S_t);
                S_max = std::max(S_max, S_t);
            }

            sumPayoff += computePayoff(S_t, S_min, S_max);

        }

        return (sumPayoff / static_cast<double>(N)) * exp(-marketData_->getR() * option_->getT());
    }

    // Floating Stike Lookback
    FloatingStrikeLookbackMCPricer::FloatingStrikeLookbackMCPricer(
        std::shared_ptr<FloatingStrikeLookbackOption> option,
        std::shared_ptr<IMarketData> marketData,
        std::shared_ptr<StockPriceModel> stockModel,
        std::shared_ptr<NumberGenerarator> generator,
        const unsigned int &steps)
    : LookbackMCPricer(std::move(option),std::move(marketData),
        std::move(stockModel), std::move(generator), steps) {}

    double FloatingStrikeLookbackMCPricer::computePayoff(const double &S_t, const double &S_min,
    const double &S_max) const {
        // Choose min for call and max for put
        return option_->getPayoff().getPayoffType() == PayoffType::Call
               ? option_->payoff(S_t, S_min)  // max(S_T - S_min, 0)
               : option_->payoff(S_t, S_max); // max(S_max - S_T, 0)
    }

    // Fixed Stike Lookback
    FixedStrikeLookbackMCPricer::FixedStrikeLookbackMCPricer(std::shared_ptr<FixedStrikeLookbackOption> option,
        std::shared_ptr<IMarketData> marketData,
        std::shared_ptr<StockPriceModel> stockModel,
        std::shared_ptr<NumberGenerarator> generator,
        const unsigned int &steps)
    : LookbackMCPricer(std::move(option),std::move(marketData),
        std::move(stockModel), std::move(generator), steps) {}

    double FixedStrikeLookbackMCPricer::computePayoff(const double &S_t, const double &S_min,
    const double &S_max) const {
        return option_->getPayoff().getPayoffType() == PayoffType::Call
               ? option_->payoff(S_max)  // max(S_max - K, 0)
               : option_->payoff(S_min); // max(K - S_min, 0)
    }

}
