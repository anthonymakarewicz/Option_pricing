#include "option/single_path/double_digital_option.h"
#include "option/single_path/factory_double_digital_option.h"
#include "payoff/double_strikes/factory_payoff_double_digital.h"
#include <market_data/market_data.h>

namespace OptionPricer {
    std::unique_ptr<Payoff> DoubleDigitalOptionFactory::createSpecificPayoff(const ParameterObject &params,
            const std::string &type) {
        return PayoffDoubleDigitalFactory::createPayoff(type, params.getParameter<double>("K1"),
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

    std::string DoubleDigitalOptionFactory::invalidParams(const std::string &option_type) const {
        std::string baseMessage = OptionFactory::invalidParams(option_type);
        if (size_t strikePos = baseMessage.find("K (double) for strike"); strikePos != std::string::npos) {
            baseMessage.replace(strikePos, 24, "K1 (double) for 1st strike\n  - K2 (double) for 2nd strike");
        }
        return baseMessage;
    }

    std::string DoubleDigitalOptionFactory::getType(const std::string& type) const {
        return "Double Digital Option";
    }
}
