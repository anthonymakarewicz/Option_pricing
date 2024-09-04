#ifndef FACTORY_BARRIER_OPTION_H
#define FACTORY_BARRIER_OPTION_H

#include <payoff/single_strike/base_payoff_single_strike.h>
#include "option/base_factory_option.h"
#include "option/path_dependent/barrier_option.h"

namespace OptionPricer {

    // Knock-In Barrier Factory
    class KnockInBarrierOptionFactory final: public OptionFactory<KnockInBarrierOption, PayoffSingleStrike> {
        std::unique_ptr<PayoffSingleStrike> createSpecificPayoff(const ParameterObject& params, const PayoffType& type) override;

        std::shared_ptr<KnockInBarrierOption> createSpecificOption(
            const ParameterObject& params,
            std::unique_ptr<PayoffSingleStrike> payoff,
            const std::shared_ptr<IMarketData>& marketData) override;

        std::string getType(const PayoffType& type) const override;
    };

    // Knock-Out Barrier Factory
    class KnockOutBarrierOptionFactory final: public OptionFactory<KnockOutBarrierOption, PayoffSingleStrike> {
        std::unique_ptr<PayoffSingleStrike> createSpecificPayoff(const ParameterObject& params, const PayoffType& type) override;

        std::shared_ptr<KnockOutBarrierOption> createSpecificOption(
            const ParameterObject& params,
            std::unique_ptr<PayoffSingleStrike> payoff,
            const std::shared_ptr<IMarketData>& marketData) override;

        std::string getType(const PayoffType& type) const override;
    };

}

#endif //FACTORY_BARRIER_OPTION_H
