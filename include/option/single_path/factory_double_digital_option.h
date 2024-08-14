#ifndef FACTORY_DOUBLE_DIGITAL_OPTION_H
#define FACTORY_DOUBLE_DIGITAL_OPTION_H

#include <option/base_factory_option.h>
#include "option/single_path/double_digital_option.h"

namespace OptionPricer {
    class DoubleDigitalOptionFactory final: public OptionFactory<DoubleDigitalOption> {
        std::unique_ptr<Payoff> createSpecificPayoff(const ParameterObject& params, const PayoffType& type) override;

        std::shared_ptr<DoubleDigitalOption> createSpecificOption(const ParameterObject& params,
                                                               std::unique_ptr<Payoff> payoff,
                                                               const std::shared_ptr<IMarketData>& marketData) override;

        std::string invalidParams(const std::string& option_type) const override;
        std::string getType(const PayoffType& type) const override;
    };
}

#endif //FACTORY_DOUBLE_DIGITAL_OPTION_H
