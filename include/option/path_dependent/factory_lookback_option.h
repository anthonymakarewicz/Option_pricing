#ifndef FACTORY_LOOKBACK_OPTION_H
#define FACTORY_LOOKBACK_OPTION_H

#include <payoff/payoff_floating_strike_lookback.h>
#include <payoff/single_strike/base_payoff_single_strike.h>
#include "option/base_factory_option.h"
#include "option/path_dependent/lookback_option.h"

namespace OptionPricer {

    // Floating Strike Lookback Factory
    class FloatingStrikeLookbackOptionFactory final: public OptionFactory<FloatingStrikeLookbackOption,
                                                                          PayoffLookbackFloatingStrike> {
    public:
        std::unique_ptr<PayoffLookbackFloatingStrike> createSpecificPayoff(const ParameterObject& params,
                                                                           const PayoffType& type) override;

        std::shared_ptr<FloatingStrikeLookbackOption> createSpecificOption(const ParameterObject& params,
                                                     std::unique_ptr<PayoffLookbackFloatingStrike> payoff,
                                                     const std::shared_ptr<IMarketData>& marketData) override;

        std::string getType(const PayoffType& type) const override;
    };

    // Fixed Strike Lookback Factory
    class FixedStrikeLookbackOptionFactory final: public OptionFactory<FixedStrikeLookbackOption, PayoffSingleStrike> {
    public:
        std::unique_ptr<PayoffSingleStrike> createSpecificPayoff(const ParameterObject& params,
                                                                 const PayoffType& type) override;
        std::shared_ptr<FixedStrikeLookbackOption> createSpecificOption(const ParameterObject& params,
                                                     std::unique_ptr<PayoffSingleStrike> payoff,
                                                     const std::shared_ptr<IMarketData>& marketData) override;
        std::string getType(const PayoffType& type) const override;
    };

}

#endif //FACTORY_LOOKBACK_OPTION_H
