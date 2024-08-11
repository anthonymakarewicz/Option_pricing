#include "option/path_dependent/factory_asian_option.h"
#include "option/path_dependent/asian_option.h"
#include "market_data/market_data.h"
#include "payoff/single_strike/payoff_vanilla.h"

namespace OptionPricer {
    // ArithmeticAsianOptionFactory
    std::unique_ptr<Payoff> ArithmeticAsianOptionFactory::createSpecificPayoff(const ParameterObject &params,
            const PayoffType& type) {
        return std::make_unique<PayoffVanilla>(type, params.getParameter<double>("K"));
    }

    std::shared_ptr<Option> ArithmeticAsianOptionFactory::createSpecificOption(const ParameterObject &params,
    std::unique_ptr<Payoff> payoff, const std::shared_ptr<IMarketData>& marketData) {
        return std::shared_ptr<Option>(new ArithmeticAsianOption(
            params.getParameter<std::string>("ticker"),
            std::move(payoff),
            params.getParameter<double>("T"),
            marketData
        ));
    }

    std::string ArithmeticAsianOptionFactory::getType(const PayoffType& type) const {
        return "Arithmetic Asian  " + PayoffTypeToString(type) + " Option";
    }

    // GeometricAsianOptionFactory
    std::unique_ptr<Payoff> GeometricAsianOptionFactory::createSpecificPayoff(const ParameterObject &params,
            const PayoffType& type) {
        return std::make_unique<PayoffVanilla>(type, params.getParameter<double>("K"));
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

    std::string GeometricAsianOptionFactory::getType(const PayoffType& type) const {
        return "Geometric Asian  " + PayoffTypeToString(type) + " Option";
    }
}