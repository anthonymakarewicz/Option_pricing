#ifndef FACTORY_PAYOFF_DOUBLE_STRIKES_H
#define FACTORY_PAYOFF_DOUBLE_STRIKES_H

#include "payoff/base_payoff.h"
#include "payoff/factory_payoff.h"

namespace OptionPricer {
    class PayoffDoubleStrikesFactory : public PayoffFactory {
    public:
        [[nodiscard]] virtual std::unique_ptr<Payoff> createPayoff(const std::string& type,
            const double& K1, const double& K2) const = 0;
    };
}

#endif //FACTORY_PAYOFF_DOUBLE_STRIKES_H
