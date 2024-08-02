#include "payoff/single_strike/factory_payoff_digital.h"
#include "option/single_path/factory_digital_option.h"
#include "option/single_path/digital_option.h"
#include <market_data/market_data.h>

namespace OptionPricer {
    std::unique_ptr<Payoff> DigitalOptionFactory::createSpecificPayoff(const ParameterObject &params,
            const std::string &type) {
        return PayoffDigitalFactory::createPayoff(type, params.getParameter<double>("K"));
    }

    std::shared_ptr<Option> DigitalOptionFactory::createSpecificOption(const ParameterObject &params,
    std::unique_ptr<Payoff> payoff, const std::shared_ptr<IMarketData>& marketData) {
        return std::shared_ptr<SinglePathOption>(new DigitalOption(
            params.getParameter<std::string>("ticker"),
            std::move(payoff),
            params.getParameter<double>("T"),
            marketData
        ));
    }

    std::string DigitalOptionFactory::getType(const std::string& type) const {
        return "Digital " + type + " Option";
    }
}
