#include "payoff/single_strike/factory_payoff_vanilla.h"
#include "option/path_dependent/factory_american_option.h"
#include "option/path_dependent/american_option.h"
#include <market_data/market_data.h>

namespace OptionPricer {
    std::unique_ptr<Payoff> AmericanOptionFactory::createSpecificPayoff(const ParameterObject &params,
            const std::string &type) {
        return PayoffVanillaFactory::createPayoff(type, params.getParameter<double>("K"));
    }

    std::shared_ptr<Option> AmericanOptionFactory::createSpecificOption(const ParameterObject &params,
    std::unique_ptr<Payoff> payoff, const std::shared_ptr<IMarketData>& marketData) {
        return std::shared_ptr<PathDependentOption>(new AmericanOption(
            params.getParameter<std::string>("ticker"),
            std::move(payoff),
            params.getParameter<double>("T"),
            marketData
        ));
    }

    std::string AmericanOptionFactory::getType(const std::string& type) const {
        return "American " + type + " Option";
    }
}
