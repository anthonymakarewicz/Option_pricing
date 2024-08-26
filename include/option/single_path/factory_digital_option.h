#ifndef FACTORY_DIGITAL_OPTION_H
#define FACTORY_DIGITAL_OPTION_H

#include <payoff/single_strike/base_payoff_single_strike.h>
#include "option/base_factory_option.h"
#include "option/single_path/digital_option.h"

namespace OptionPricer {

    class DigitalOptionFactory final: public OptionFactory<DigitalOption, PayoffSingleStrike> {
        std::unique_ptr<PayoffSingleStrike> createSpecificPayoff(const ParameterObject& params,
                                                                 const PayoffType& type) override;

        std::shared_ptr<DigitalOption> createSpecificOption(const ParameterObject& params,
                                                            std::unique_ptr<PayoffSingleStrike> payoff,
                                                            const std::shared_ptr<IMarketData>& marketData) override;

        std::string getType(const PayoffType& type) const override;
    };
}

#endif //FACTORY_DIGITAL_OPTION_H
