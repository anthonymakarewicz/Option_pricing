#include "option/single_path/factory_digital_option.h"
#include "payoff/single_strike/payoff_digital.h"
#include <market_data/market_data.h>

namespace OptionPricer {
    std::unique_ptr<Payoff> DigitalOptionFactory::createSpecificPayoff(const ParameterObject &params,
            const PayoffType& type) {
        return std::make_unique<PayoffDigital>(type, params.getParameter<double>("K"));
    }

    std::shared_ptr<DigitalOption> DigitalOptionFactory::createSpecificOption(const ParameterObject &params,
    std::unique_ptr<Payoff> payoff, const std::shared_ptr<IMarketData>& marketData) {
        return std::shared_ptr<DigitalOption>(new DigitalOption(
            params.getParameter<std::string>("ticker"),
            std::move(payoff),
            params.getParameter<double>("T"),
            marketData
        ));
    }

    std::string DigitalOptionFactory::getType(const PayoffType& type) const {
        return "Digital " + PayoffTypeToString(type) + " Option";
    }
}
