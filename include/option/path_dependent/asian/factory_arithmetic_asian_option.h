#ifndef FACTORY_ARITHMETIC_ASIAN_OPTION_H
#define FACTORY_ARITHMETIC_ASIAN_OPTION_H

#include "option/factory_option.h"

namespace OptionPricer {
    class ArithmeticAsianOptionFactory final: public OptionFactory {
        std::unique_ptr<Payoff> createSpecificPayoff(const ParameterObject& params, const std::string& type) override;

        std::shared_ptr<Option> createSpecificOption(const ParameterObject& params,
                                                               std::unique_ptr<Payoff> payoff,
                                                               const std::shared_ptr<IMarketData>& marketData) override;

        std::string getType(const std::string& type) const override;
    };
}

#endif //FACTORY_ARITHMETIC_ASIAN_OPTION_H
