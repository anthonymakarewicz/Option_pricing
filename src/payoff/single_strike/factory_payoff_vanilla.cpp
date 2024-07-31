#include "payoff/single_strike/factory_payoff_vanilla.h"
#include "payoff/single_strike/payoff_vanilla_call.h"
#include "payoff/single_strike/payoff_vanilla_put.h"

namespace OptionPricer {
    std::unique_ptr<Payoff> PayoffVanillaFactory::createPayoff(const std::string& type, const double &K) const {
        if (type == "call") {
            return std::make_unique<PayoffVanillaCall>(K);
        }
        if (type == "put") {
            return std::make_unique<PayoffVanillaPut>(K);
        }
        throw std::invalid_argument("Invalid option type: " + type);
    }
}