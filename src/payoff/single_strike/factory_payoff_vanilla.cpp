#include <algorithm>
#include <cctype>

#include "payoff/single_strike/factory_payoff_vanilla.h"
#include "payoff/single_strike/payoff_vanilla_call.h"
#include "payoff/single_strike/payoff_vanilla_put.h"

namespace OptionPricer {
    std::unique_ptr<Payoff> PayoffVanillaFactory::createPayoff(const std::string& type, const double &K) {
        // Convert the type string to lowercase with ranges C++20
        std::string typeLower = type;
        std::ranges::transform(typeLower, typeLower.begin(),
            [](unsigned char c){ return std::tolower(c); });

        if (typeLower == "call") {
            return std::make_unique<PayoffVanillaCall>(K);
        }
        if (typeLower == "put") {
            return std::make_unique<PayoffVanillaPut>(K);
        }
        throw std::invalid_argument("Invalid option type: " + type);
    }
}