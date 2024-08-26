#ifndef FACTORY_ASIAN_OPTION_H
#define FACTORY_ASIAN_OPTION_H

#include <payoff/single_strike/base_payoff_single_strike.h>
#include "option/base_factory_option.h"
#include "option/path_dependent/asian_option.h"

namespace OptionPricer {

    // ArithmeticAsianOptionFactory
    class ArithmeticAsianOptionFactory final: public OptionFactory<ArithmeticAsianOption, PayoffSingleStrike> {
        std::unique_ptr<PayoffSingleStrike> createSpecificPayoff(const ParameterObject& params, const PayoffType& type) override;
        std::shared_ptr<ArithmeticAsianOption> createSpecificOption(const ParameterObject& params,
                                                     std::unique_ptr<PayoffSingleStrike> payoff,
                                                     const std::shared_ptr<IMarketData>& marketData) override;
        std::string getType(const PayoffType& type) const override;
    };

    // GeometricAsianOptionFactory
    class GeometricAsianOptionFactory final: public OptionFactory<GeometricAsianOption, PayoffSingleStrike> {
        std::unique_ptr<PayoffSingleStrike> createSpecificPayoff(const ParameterObject& params, const PayoffType& type) override;
        std::shared_ptr<GeometricAsianOption> createSpecificOption(const ParameterObject& params,
                                                     std::unique_ptr<PayoffSingleStrike> payoff,
                                                     const std::shared_ptr<IMarketData>& marketData) override;
        std::string getType(const PayoffType& type) const override;
    };

}

#endif //FACTORY_ASIAN_OPTION_H
