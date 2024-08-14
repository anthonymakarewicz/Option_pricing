#ifndef FACTORY_EUROPEAN_OPTION_H
#define FACTORY_EUROPEAN_OPTION_H

#include "option/single_path/european_option.h"
#include "option/base_factory_option.h"

namespace OptionPricer {

    class EuropeanOptionFactory final: public OptionFactory<EuropeanOption> {
        // Could potentially make the createSpecificOption specific to each Factory thus returnign
        // here returning a EuropeanOption, hwoever for createSpecificPayoff it might be ok to define it as pure
        // virtual inside the OptionFatcory as well as the getType method
        std::unique_ptr<Payoff> createSpecificPayoff(const ParameterObject& params, const PayoffType& type) override;

        std::shared_ptr<EuropeanOption> createSpecificOption(const ParameterObject& params,
                                                     std::unique_ptr<Payoff> payoff,
                                                     const std::shared_ptr<IMarketData>& marketData) override;

        std::string getType(const PayoffType& type) const override;

    };
}

#endif //FACTORY_EUROPEAN_OPTION_H
