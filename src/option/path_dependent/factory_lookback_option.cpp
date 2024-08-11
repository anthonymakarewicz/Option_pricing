#include "option/path_dependent/factory_lookback_option.h"
#include "option/path_dependent/lookback_option.h"
#include "market_data/market_data.h"
#include "payoff/single_strike/payoff_vanilla.h"
#include "payoff/payoff_floating_strike_lookback.h"

namespace OptionPricer {

    // Floating Strike Lookback Factory
    std::unique_ptr<Payoff> FloatingStrikeLookbackOptionFactory::createSpecificPayoff(const ParameterObject &params,
            const PayoffType& type) {
        return std::make_unique<PayoffLookbackFloatingStrike>(type);
    }

    std::shared_ptr<Option> FloatingStrikeLookbackOptionFactory::createSpecificOption(const ParameterObject &params,
    std::unique_ptr<Payoff> payoff, const std::shared_ptr<IMarketData>& marketData) {
        return std::shared_ptr<Option>(new FloatingStrikeLookbackOption(
            params.getParameter<std::string>("ticker"),
            std::move(payoff),
            params.getParameter<double>("T"),
            marketData
        ));
    }

    std::string FloatingStrikeLookbackOptionFactory::getType(const PayoffType& type) const {
        return "Floating Strike Lookback " + PayoffTypeToString(type) + " Option";
    }

    // Fiex Strike Lookback Factory
    std::unique_ptr<Payoff> FixedStrikeLookbackOptionFactory::createSpecificPayoff(const ParameterObject &params,
            const PayoffType& type) {
        return std::make_unique<PayoffVanilla>(type, params.getParameter<double>("K"));
    }

    std::shared_ptr<Option> FixedStrikeLookbackOptionFactory::createSpecificOption(const ParameterObject &params,
    std::unique_ptr<Payoff> payoff, const std::shared_ptr<IMarketData>& marketData) {
        return std::shared_ptr<Option>(new FixedStrikeLookbackOption(
            params.getParameter<std::string>("ticker"),
            std::move(payoff),
            params.getParameter<double>("T"),
            marketData
        ));
    }

    std::string FixedStrikeLookbackOptionFactory::getType(const PayoffType& type) const {
        return "Fixed Strike Lookback " + PayoffTypeToString(type) + " Option";
    }

}