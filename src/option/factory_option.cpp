#include "option/factory_option.h"
#include "market_data/market_data.h"

namespace OptionPricer {
    OptionFactory::~OptionFactory() = default;

    std::shared_ptr<Option> OptionFactory::createCallOption(const ParameterObject &params) {
        return createOption(params, "Call");
    }

    std::shared_ptr<Option> OptionFactory::createPutOption(const ParameterObject &params) {
        return createOption(params, "Put");
    }

    std::shared_ptr<Option> OptionFactory::createOption(const ParameterObject &params,
        const std::string &type) {
        auto marketData = MarketData::getInstance();
        std::shared_ptr<Option> option = nullptr;

        try {
            auto payoff = createSpecificPayoff(params, type);
            option = createSpecificOption(params, std::move(payoff), marketData);
        } catch (const std::invalid_argument& e) {
            const std::string err = std::string(e.what()) + "\n" + invalidParams(getType(type));
            throw std::invalid_argument(err);
        }

        option->initialize();
        return option;
    }

    std::string OptionFactory::invalidParams(const std::string &option_type) const {
        return "Invalid parameters for " + option_type + "\n"
          "Expected parameters:\n"
          "  - ticker (string) for ticker symbol\n"
          "  - T (double) for maturity\n"
          "  - K (double) for strike\n";
    }
}
