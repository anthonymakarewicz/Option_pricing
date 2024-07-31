#include "payoff/single_strike/factory_payoff_digital.h"
#include "payoff/single_strike/payoff_digital_call.h"
#include "payoff/single_strike/payoff_digital_put.h"

namespace OptionPricer {
    std::unique_ptr<Payoff> PayoffDigitalFactory::createPayoff(const std::string& type, const double& K) const {
        if (type == "call") {
            return std::make_unique<PayoffDigitalCall>(K);
        }
        if (type == "put") {
            return std::make_unique<PayoffDigitalPut>(K);
        }
        throw std::invalid_argument("Invalid option type: " + type);
    }
}