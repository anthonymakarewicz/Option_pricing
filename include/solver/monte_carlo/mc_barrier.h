#ifndef MC_BARRIER_H
#define MC_BARRIER_H

#include "solver/monte_carlo/base_mc.h"
#include "option/path_dependent/barrier_option.h"

namespace OptionPricer {

    class BarrierMCPricer : public MCPricer {
    public:
        BarrierMCPricer(std::shared_ptr<BarrierOption> option,
                        std::shared_ptr<IMarketData> marketData,
                        std::shared_ptr<StockModel> stockModel);

        [[nodiscard]] double calculatePrice(const unsigned long& N) const override;

    protected:
        virtual bool checkHasCrossed(const double& S_t, bool& hasCrossed) const = 0;
        virtual double computePayoff(const double& S_T, const bool& hasCrossed) const = 0;

        std::shared_ptr<BarrierOption> option_;
    };

    class KnockInBarrierMCPricer final: public BarrierMCPricer {
    public:
        KnockInBarrierMCPricer(std::shared_ptr<KnockInBarrierOption> option,
                               std::shared_ptr<IMarketData> marketData,
                               std::shared_ptr<StockModel> stockModel);

    protected:
        bool checkHasCrossed(const double& S_t, bool& hasCrossed) const override;
        double computePayoff(const double& S_T, const bool& hasCrossed) const override;
    };

    class KnockOutBarrierMCPricer final: public BarrierMCPricer {
    public:
        KnockOutBarrierMCPricer(std::shared_ptr<KnockOutBarrierOption> option,
                                std::shared_ptr<IMarketData> marketData,
                                std::shared_ptr<StockModel> stockModel);

    protected:
        bool checkHasCrossed(const double& S_t, bool& hasCrossed) const override;
        double computePayoff(const double& S_T, const bool& hasCrossed) const override;
    };

}

#endif //MC_BARRIER_H
