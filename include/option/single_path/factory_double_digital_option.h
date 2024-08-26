#ifndef FACTORY_DOUBLE_DIGITAL_OPTION_H
#define FACTORY_DOUBLE_DIGITAL_OPTION_H

#include <option/base_factory_option.h>
#include "option/single_path/double_digital_option.h"
#include "payoff/double_strikes/base_payoff_double_strikes.h"

namespace OptionPricer {
    class DoubleDigitalOptionFactory final: public OptionFactory<DoubleDigitalOption, PayoffDoubleStrikes> {
        std::unique_ptr<PayoffDoubleStrikes> createSpecificPayoff(const ParameterObject& params,
                                                                  const PayoffType& type) override;

        std::shared_ptr<DoubleDigitalOption> createSpecificOption(const ParameterObject& params,
                                                                  std::unique_ptr<PayoffDoubleStrikes> payoff,
                                                                  const std::shared_ptr<IMarketData>& marketData) override;

        std::string invalidParams(const std::string& option_type) const override;
        std::string getType(const PayoffType& type) const override;
    };
}

#endif //FACTORY_DOUBLE_DIGITAL_OPTION_H