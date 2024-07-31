#ifndef FACTORY_PAYOFF_SINGLE_STRIKE_H
#define FACTORY_PAYOFF_SINGLE_STRIKE_H

#include "payoff/base_payoff.h"
#include "payoff/factory_payoff.h"

namespace OptionPricer {
    class PayoffSingleStrikeFactory : public PayoffFactory {
    public:
        [[nodiscard]] virtual std::unique_ptr<Payoff> createPayoff(const std::string& type, const double& K1) const = 0;
    };
}

#endif //FACTORY_PAYOFF_SINGLE_STRIKE_H
