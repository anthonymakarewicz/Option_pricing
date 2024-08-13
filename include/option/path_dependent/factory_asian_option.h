#ifndef FACTORY_ASIAN_OPTION_H
#define FACTORY_ASIAN_OPTION_H

#include "option/base_factory_option.h"
#include "option/path_dependent/asian_option.h"

namespace OptionPricer {

    class ArithmeticAsianOptionFactory final: public OptionFactory<ArithmeticAsianOption> {
        std::unique_ptr<Payoff> createSpecificPayoff(const ParameterObject& params, const PayoffType& type) override;
        std::shared_ptr<ArithmeticAsianOption> createSpecificOption(const ParameterObject& params,
                                                     std::unique_ptr<Payoff> payoff,
                                                     const std::shared_ptr<IMarketData>& marketData) override;
        std::string getType(const PayoffType& type) const override;
    };

    class GeometricAsianOptionFactory final: public OptionFactory<GeometricAsianOption> {
        std::unique_ptr<Payoff> createSpecificPayoff(const ParameterObject& params, const PayoffType& type) override;
        std::shared_ptr<GeometricAsianOption> createSpecificOption(const ParameterObject& params,
                                                     std::unique_ptr<Payoff> payoff,
                                                     const std::shared_ptr<IMarketData>& marketData) override;
        std::string getType(const PayoffType& type) const override;
    };

}

#endif //FACTORY_ASIAN_OPTION_H
