#include "option/path_dependent/asian/factory_geometric_asian_option.h"
#include "option/path_dependent/asian/geometric_asian_option.h"
#include "payoff/single_strike/base_payoff_vanilla.h"
#include <payoff/single_strike/factory_payoff_vanilla.h>
#include <market_data/market_data.h>

namespace OptionPricer {
    std::unique_ptr<Payoff> GeometricAsianOptionFactory::createSpecificPayoff(const ParameterObject &params,
            const std::string &type) {
        return PayoffVanillaFactory::createPayoff(type, params.getParameter<double>("K"));
    }

    std::shared_ptr<Option> GeometricAsianOptionFactory::createSpecificOption(const ParameterObject &params,
    std::unique_ptr<Payoff> payoff, const std::shared_ptr<IMarketData>& marketData) {
        return std::shared_ptr<Option>(new GeometricAsianOption(
            params.getParameter<std::string>("ticker"),
            std::move(payoff),
            params.getParameter<double>("T"),
            marketData
        ));
    }

    std::string GeometricAsianOptionFactory::getType(const std::string& type) const {
        return "Geometric Asian  " + type + " Option";
    }
}