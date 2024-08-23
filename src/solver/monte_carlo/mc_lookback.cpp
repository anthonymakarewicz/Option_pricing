#include "solver/monte_carlo/mc_lookback.h"

namespace OptionPricer {

    // Base Lookback
    LookbackMCPricer::LookbackMCPricer(std::shared_ptr<LookbackOption> option,
                                       std::shared_ptr<IMarketData> marketData,
                                       std::shared_ptr<StockModel> stockModel)
    : MCPricer(std::move(marketData),std::move(stockModel)),
      option_(std::move(option)) {}

    double LookbackMCPricer::calculatePrice(const unsigned long &N) const {
        double sumPayoff = 0.0;
        const unsigned int steps = stockModel_->getSteps();
        const double discountFactor = exp(-marketData_->getR()*option_->getT());

        for (int i = 0; i < N; ++i) {
            std::vector<double> S = stockModel_->simulatePrices(option_->getT());
            double S_min = std::numeric_limits<double>::infinity();
            double S_max = -std::numeric_limits<double>::infinity();

            for (int t = 0; t < steps; ++t) {
                S_min = std::min(S_min, S[t]);
                S_max = std::max(S_max, S[t]);
            }

            sumPayoff += computePayoff(S[steps-1], S_min, S_max);
        }

        return (sumPayoff / static_cast<double>(N)) * discountFactor;
    }

    // Floating Strike Lookback
    FloatingStrikeLookbackMCPricer::FloatingStrikeLookbackMCPricer(
        std::shared_ptr<FloatingStrikeLookbackOption> option,
        std::shared_ptr<IMarketData> marketData,
        std::shared_ptr<StockModel> stockModel)
    : LookbackMCPricer(std::move(option),std::move(marketData),
        std::move(stockModel)) {}

    double FloatingStrikeLookbackMCPricer::computePayoff(const double &S_T,
                                                         const double &S_min,
                                                         const double &S_max) const {
        return option_->getPayoff().getPayoffType() == PayoffType::Call
               ? option_->payoff(S_T, S_min)  // max(S_T - S_min, 0)
               : option_->payoff(S_T, S_max); // max(S_max - S_T, 0)
    }

    // Fixed Strike Lookback
    FixedStrikeLookbackMCPricer::FixedStrikeLookbackMCPricer(
        std::shared_ptr<FixedStrikeLookbackOption> option,
        std::shared_ptr<IMarketData> marketData,
        std::shared_ptr<StockModel> stockModel)
    : LookbackMCPricer(std::move(option),std::move(marketData),
        std::move(stockModel)) {}

    double FixedStrikeLookbackMCPricer::computePayoff(const double &S_T,
                                                      const double &S_min,
                                                      const double &S_max) const {
        return option_->getPayoff().getPayoffType() == PayoffType::Call
               ? option_->payoff(S_max)  // max(S_max - K, 0)
               : option_->payoff(S_min); // max(K - S_min, 0)
    }

}
