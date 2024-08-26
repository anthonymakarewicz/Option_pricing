#ifndef FACTORY_AMERICAN_OPTION_H
#define FACTORY_AMERICAN_OPTION_H

#include "option/base_factory_option.h"
#include "option/path_dependent/american_option.h"

namespace OptionPricer {

    class AmericanOptionFactory final: public OptionFactory<AmericanOption, PayoffSingleStrike> {
        std::unique_ptr<PayoffSingleStrike> createSpecificPayoff(const ParameterObject& params,
                                                     const PayoffType& type) override;

        std::shared_ptr<AmericanOption> createSpecificOption(const ParameterObject& params,
                                                             std::unique_ptr<PayoffSingleStrike> payoff,
                                                             const std::shared_ptr<IMarketData>& marketData) override;

        std::string getType(const PayoffType& type) const override;
    };

}

#endif //FACTORY_AMERICAN_OPTION_H
