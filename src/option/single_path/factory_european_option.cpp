#include "payoff/single_strike/payoff_vanilla.h"
#include "option/single_path/factory_european_option.h"
#include <market_data/market_data.h>

namespace OptionPricer {
    std::unique_ptr<PayoffSingleStrike> EuropeanOptionFactory::createSpecificPayoff(const ParameterObject &params,
            const PayoffType& type) {
        return std::make_unique<PayoffVanilla>(type, params.getParameter<double>("K"));
    }

    std::shared_ptr<EuropeanOption> EuropeanOptionFactory::createSpecificOption(const ParameterObject &params,
    std::unique_ptr<PayoffSingleStrike> payoff, const std::shared_ptr<IMarketData>& marketData) {
        return std::shared_ptr<EuropeanOption>(new EuropeanOption(
            params.getParameter<std::string>("ticker"),
            std::move(payoff),
            params.getParameter<double>("T"),
            marketData
        ));
    }

    std::string EuropeanOptionFactory::getType(const PayoffType& type) const {
        return "European " + PayoffTypeToString(type) + " Option";
    }
}
