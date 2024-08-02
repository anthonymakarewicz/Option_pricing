#ifndef FACTORY_PAYOFF_DOUBLE_DIGITAL_H
#define FACTORY_PAYOFF_DOUBLE_DIGITAL_H

#include "payoff/base_payoff.h"

namespace OptionPricer {
    class PayoffDoubleDigitalFactory final {
    public:
        [[nodiscard]] static std::unique_ptr<Payoff> createPayoff(const std::string& type,
            const double& K1, const double& K2);
    };
}

#endif //FACTORY_PAYOFF_DOUBLE_DIGITAL_H
