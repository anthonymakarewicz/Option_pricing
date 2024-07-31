#ifndef FACTORY_PAYOFF_VANILLA_H
#define FACTORY_PAYOFF_VANILLA_H

#include "factory_payoff_single_strike.h"

namespace OptionPricer {
    class PayoffVanillaFactory final: public PayoffSingleStrikeFactory {
    public:
        [[nodiscard]] std::unique_ptr<Payoff> createPayoff(const std::string& type, const double &K) const override;
    };
}

#endif //FACTORY_PAYOFF_VANILLA_H
