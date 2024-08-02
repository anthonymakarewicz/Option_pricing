#ifndef FACTORY_PAYOFF_VANILLA_H
#define FACTORY_PAYOFF_VANILLA_H

#include <string>
#include "payoff/base_payoff.h"

namespace OptionPricer {
    class PayoffVanillaFactory final {
    public:
        [[nodiscard]] static std::unique_ptr<Payoff> createPayoff(const std::string& type, const double &K);
    };
}

#endif //FACTORY_PAYOFF_VANILLA_H
