#include "payoff/double_strikes/factory_payoff_double_digital.h"
#include "payoff/double_strikes/payoff_double_digital.h"

namespace OptionPricer {
    std::unique_ptr<Payoff> PayoffDoubleDigitalFactory::createPayoff(const std::string& type,
            const double& K1, const double& K2) {
        return std::make_unique<PayoffDoubleDigital>(K1, K2);
    }
}