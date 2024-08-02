#include "payoff/single_strike/factory_payoff_vanilla.h"
#include "option/single_path/factory_european_option.h"
#include "option/single_path/european_option.h"
#include <market_data/market_data.h>

namespace OptionPricer {
    std::unique_ptr<Payoff> EuropeanOptionFactory::createSpecificPayoff(const ParameterObject &params,
            const std::string &type) {
        return PayoffVanillaFactory::createPayoff(type, params.getParameter<double>("K"));
    }

    std::shared_ptr<Option> EuropeanOptionFactory::createSpecificOption(const ParameterObject &params,
    std::unique_ptr<Payoff> payoff, const std::shared_ptr<IMarketData>& marketData) {
        return std::shared_ptr<SinglePathOption>(new EuropeanOption(
            params.getParameter<std::string>("ticker"),
            std::move(payoff),
            params.getParameter<double>("T"),
            marketData
        ));
    }

    std::string EuropeanOptionFactory::getType(const std::string& type) const {
        return "European " + type + " Option";
    }
}
