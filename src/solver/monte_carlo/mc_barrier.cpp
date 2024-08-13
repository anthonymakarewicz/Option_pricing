#include "solver/monte_carlo/mc_barrier.h"

namespace OptionPricer {

    // Base Barrier
    BarrierMCPricer::BarrierMCPricer(std::shared_ptr<BarrierOption> option,
                                     std::shared_ptr<IMarketData> marketData,
                                     std::shared_ptr<StockPriceModel> stockModel,
                                     std::shared_ptr<NumberGenerarator> generator,
                                     const unsigned int& steps)
    : PathDependentMCPricer(std::move(marketData),std::move(stockModel),
        std::move(generator), steps), option_(std::move(option)) {}

    double BarrierMCPricer::calculate_price(const unsigned long &N) const {
        double sumPayoff = 0.0;
        const double dt = option_->getT() / static_cast<double>(steps_);

        for (int i = 0; i < N; ++i) {
            double S_t = marketData_->getStockData(option_->getID())->getPrice();
            bool hasCrossed = false;

            for (int step = 0; step < steps_; ++step) {
                double z = generator_->generate(step);
                S_t *= stockModel_->simulateStepPrice(dt, z);

                if (checkHasCrossed(S_t, hasCrossed)) {
                    break;
                }
            }

            sumPayoff += computePayoff(S_t, hasCrossed);
        }

        return (sumPayoff / static_cast<double>(N)) * exp(-marketData_->getR()*option_->getT());
    }

    // Knock In
    KnockInBarrierMCPricer::KnockInBarrierMCPricer(std::shared_ptr<KnockInBarrierOption> option,
                                     std::shared_ptr<IMarketData> marketData,
                                     std::shared_ptr<StockPriceModel> stockModel,
                                     std::shared_ptr<NumberGenerarator> generator,
                                     const unsigned int& steps)
    : BarrierMCPricer(std::move(option), std::move(marketData),
    std::move(stockModel), std::move(generator), steps) {}

    bool KnockInBarrierMCPricer::checkHasCrossed(const double &S_t, bool &hasCrossed) const {
        if (option_->isActive(S_t)) {
            hasCrossed = true;
        }
        return false; // Never exit early for Knock-In
    }

    double KnockInBarrierMCPricer::computePayoff(const double &S_t, const bool &hasCrossed) const {
        return hasCrossed ? option_->payoff(S_t) : 0.0;
    }

    // Knock Out
    KnockOutBarrierMCPricer::KnockOutBarrierMCPricer(std::shared_ptr<KnockOutBarrierOption> option,
                                       std::shared_ptr<IMarketData> marketData,
                                       std::shared_ptr<StockPriceModel> stockModel,
                                       std::shared_ptr<NumberGenerarator> generator,
                                       const unsigned int& steps)
    : BarrierMCPricer(std::move(option), std::move(marketData),
        std::move(stockModel), std::move(generator), steps) {}

    bool KnockOutBarrierMCPricer::checkHasCrossed(const double &S_t, bool &hasCrossed) const {
        if (!option_->isActive(S_t)) {
            hasCrossed = true;
            return true; // Exit the loop early
        }
        return false; // Continue the loop
    }

    double KnockOutBarrierMCPricer::computePayoff(const double &S_t, const bool &hasCrossed) const {
        return hasCrossed ? 0.0 : option_->payoff(S_t);
    }

}

