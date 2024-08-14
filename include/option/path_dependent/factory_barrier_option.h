#ifndef FACTORY_BARRIER_OPTION_H
#define FACTORY_BARRIER_OPTION_H

#include "option/base_factory_option.h"
#include "option/path_dependent/barrier_option.h"

namespace OptionPricer {

    // Knock-In Barrier Factory
    class KnockInBarrierOptionFactory final: public OptionFactory<KnockInBarrierOption> {
        std::unique_ptr<Payoff> createSpecificPayoff(const ParameterObject& params, const PayoffType& type) override;

        std::shared_ptr<KnockInBarrierOption> createSpecificOption(
            const ParameterObject& params,
            std::unique_ptr<Payoff> payoff,
            const std::shared_ptr<IMarketData>& marketData) override;

        std::string getType(const PayoffType& type) const override;
    };

    // Knock-Out Barrier Factory
    class KnockOutBarrierOptionFactory final: public OptionFactory<KnockOutBarrierOption> {
        std::unique_ptr<Payoff> createSpecificPayoff(const ParameterObject& params, const PayoffType& type) override;

        std::shared_ptr<KnockOutBarrierOption> createSpecificOption(
            const ParameterObject& params,
            std::unique_ptr<Payoff> payoff,
            const std::shared_ptr<IMarketData>& marketData) override;

        std::string getType(const PayoffType& type) const override;
    };

}

#endif //FACTORY_BARRIER_OPTION_H
