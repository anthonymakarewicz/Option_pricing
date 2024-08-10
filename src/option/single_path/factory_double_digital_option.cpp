#include "option/single_path/double_digital_option.h"
#include "option/single_path/factory_double_digital_option.h"
#include "payoff/double_strikes/factory_payoff_double_digital.h"
#include <market_data/market_data.h>

namespace OptionPricer {
    std::unique_ptr<Payoff> DoubleDigitalOptionFactory::createSpecificPayoff(const ParameterObject &params,
            const std::string &type) {
        PayoffDoubleDigitalFactory payoffFactory;
        return payoffFactory.createPayoff(type, params.getParameter<double>("K1"),
            params.getParameter<double>("K2"));
    }

    std::shared_ptr<Option> DoubleDigitalOptionFactory::createSpecificOption(const ParameterObject &params,
    std::unique_ptr<Payoff> payoff, const std::shared_ptr<IMarketData>& marketData) {
        return std::shared_ptr<SinglePathOption>(new DoubleDigitalOption(
            params.getParameter<std::string>("ticker"),
            std::move(payoff),
            params.getParameter<double>("T"),
            marketData
        ));
    }

    std::string DoubleDigitalOptionFactory::getType(const std::string& type) const {
        return "Double Digital Option";
    }
}
