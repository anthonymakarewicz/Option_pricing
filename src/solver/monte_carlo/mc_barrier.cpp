#include "solver/monte_carlo/mc_barrier.h"

namespace OptionPricer {

    // Base Barrier
    BarrierMCPricer::BarrierMCPricer(std::shared_ptr<BarrierOption> option,
                                     std::shared_ptr<IMarketData> marketData,
                                     std::shared_ptr<StockModel> stockModel)
    : MCPricer(std::move(marketData),std::move(stockModel)),
      option_(std::move(option)) {}

    double BarrierMCPricer::calculatePrice(const unsigned long &N) const {
        double sumPayoff = 0.0;
        const unsigned int steps = stockModel_->getSteps();
        const double discountFactor = exp(-marketData_->getR()*option_->getT());

        for (int i = 0; i < N; ++i) {
            std::vector<double> S = stockModel_->simulatePrices(option_->getT());
            bool hasCrossed = false;

            for (int t = 0; t < steps; ++t) {
                if (checkHasCrossed(S[t], hasCrossed)) {
                    break;
                }
            }

            sumPayoff += computePayoff(S[steps-1], hasCrossed);
        }

        return (sumPayoff / static_cast<double>(N)) * discountFactor;
    }

    // Knock In
    KnockInBarrierMCPricer::KnockInBarrierMCPricer(std::shared_ptr<KnockInBarrierOption> option,
                                                   std::shared_ptr<IMarketData> marketData,
                                                   std::shared_ptr<StockModel> stockModel)
    : BarrierMCPricer(std::move(option), std::move(marketData),
    std::move(stockModel)) {}

    bool KnockInBarrierMCPricer::checkHasCrossed(const double &S_t, bool &hasCrossed) const {
        if (option_->isActive(S_t)) {
            hasCrossed = true;
        }
        return false; // Never exit early for Knock-In
    }

    double KnockInBarrierMCPricer::computePayoff(const double &S_T, const bool &hasCrossed) const {
        return hasCrossed ? option_->payoff(S_T) : 0.0;
    }

    // Knock Out
    KnockOutBarrierMCPricer::KnockOutBarrierMCPricer(std::shared_ptr<KnockOutBarrierOption> option,
                                                     std::shared_ptr<IMarketData> marketData,
                                                     std::shared_ptr<StockModel> stockModel)
    : BarrierMCPricer(std::move(option), std::move(marketData),
        std::move(stockModel)) {}

    bool KnockOutBarrierMCPricer::checkHasCrossed(const double &S_t, bool &hasCrossed) const {
        if (!option_->isActive(S_t)) {
            hasCrossed = true;
            return true; // Exit the loop early
        }
        return false; // Continue the loop
    }

    double KnockOutBarrierMCPricer::computePayoff(const double &S_T, const bool &hasCrossed) const {
        return hasCrossed ? 0.0 : option_->payoff(S_T);
    }

}

