#ifndef FACTORY_EUROPEAN_OPTION_H
#define FACTORY_EUROPEAN_OPTION_H

#include "option/single_path/european_option.h"
#include "option/base_factory_option.h"

namespace OptionPricer {

    class EuropeanOptionFactory final: public OptionFactory<EuropeanOption, PayoffSingleStrike> {
        std::unique_ptr<PayoffSingleStrike> createSpecificPayoff(const ParameterObject& params,
                                                                 const PayoffType& type) override;

        std::shared_ptr<EuropeanOption> createSpecificOption(const ParameterObject& params,
                                                             std::unique_ptr<PayoffSingleStrike> payoff,
                                                             const std::shared_ptr<IMarketData>& marketData) override;

        std::string getType(const PayoffType& type) const override;

    };
}

#endif //FACTORY_EUROPEAN_OPTION_H
