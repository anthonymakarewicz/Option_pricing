#include "option/single_path/factory_european_option.h"

#include <market_data/market_data.h>
#include "option/single_path/european_option.h"
#include "payoff/single_strike/factory_payoff_vanilla.h"

namespace OptionPricer {
    std::shared_ptr<SinglePathOption> EuropeanOptionFactory::createOption(const ParameterObject &params,
            const std::string &type) {
        auto marketData = MarketData::getInstance();
        std::shared_ptr<SinglePathOption> eurOption = nullptr;

        try {
            PayoffVanillaFactory payoffFactory;
            auto payoff = payoffFactory.createPayoff(type, params.getParameter<double>("K"));
            eurOption = std::shared_ptr<SinglePathOption>( new EuropeanOption(
                params.getParameter<std::string>("ticker"),
                std::move(payoff),
                params.getParameter<double>("T"),
                marketData
                ));
        } catch (const std::invalid_argument& e) {
            const std::string err = std::string(e.what()) + "\n" + invalidParams("European Option");
            throw std::invalid_argument(err); // Re-throw the caught exception
        }

        eurOption->initialize();
        return eurOption;
    }
}