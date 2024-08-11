#ifndef FACTORY_ASIAN_OPTION_H
#define FACTORY_ASIAN_OPTION_H

#include "option/factory_option.h"

namespace OptionPricer {
    class ArithmeticAsianOptionFactory final: public OptionFactory {
        std::unique_ptr<Payoff> createSpecificPayoff(const ParameterObject& params, const PayoffType& type) override;

        std::shared_ptr<Option> createSpecificOption(const ParameterObject& params,
                                                     std::unique_ptr<Payoff> payoff,
                                                     const std::shared_ptr<IMarketData>& marketData) override;

        std::string getType(const PayoffType& type) const override;
    };


    class GeometricAsianOptionFactory final: public OptionFactory {
        std::unique_ptr<Payoff> createSpecificPayoff(const ParameterObject& params, const PayoffType& type) override;

        std::shared_ptr<Option> createSpecificOption(const ParameterObject& params,
                                                     std::unique_ptr<Payoff> payoff,
                                                     const std::shared_ptr<IMarketData>& marketData) override;

        std::string getType(const PayoffType& type) const override;
    };
}

#endif //FACTORY_ASIAN_OPTION_H
