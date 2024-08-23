#ifndef MC_LOOKBACK_H
#define MC_LOOKBACK_H

#include "solver/monte_carlo/base_mc.h"
#include "option/path_dependent/lookback_option.h"

namespace OptionPricer {

        class LookbackMCPricer : public MCPricer {
        public:
            LookbackMCPricer(std::shared_ptr<LookbackOption> option,
                             std::shared_ptr<IMarketData> marketData,
                             std::shared_ptr<StockModel> stockModel);

            [[nodiscard]] double calculatePrice(const unsigned long& N) const override;

        protected:
            virtual double computePayoff(const double& S_T, const double& S_min, const double& S_max) const = 0;
            std::shared_ptr<LookbackOption> option_;
    };

    class FloatingStrikeLookbackMCPricer final: public LookbackMCPricer {
    public:
        FloatingStrikeLookbackMCPricer(std::shared_ptr<FloatingStrikeLookbackOption> option,
                                       std::shared_ptr<IMarketData> marketData,
                                       std::shared_ptr<StockModel> stockModel);

    private:
        double computePayoff(const double& S_T, const double& S_min, const double& S_max) const override;
    };

    class FixedStrikeLookbackMCPricer : public LookbackMCPricer {
    public:
        FixedStrikeLookbackMCPricer(std::shared_ptr<FixedStrikeLookbackOption> option,
                                    std::shared_ptr<IMarketData> marketData,
                                    std::shared_ptr<StockModel> stockModel);

    private:
        double computePayoff(const double& S_T, const double& S_min, const double& S_max) const override;
    };

}

#endif //MC_LOOKBACK_H
