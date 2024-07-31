#ifndef FACTORY_PAYOFF_DIGITAL_H
#define FACTORY_PAYOFF_DIGITAL_H

#include "factory_payoff_single_strike.h"
#include "payoff/factory_payoff.h"

namespace OptionPricer {
    class PayoffDigitalFactory final: public PayoffSingleStrikeFactory {
    public:
        [[nodiscard]] std::unique_ptr<Payoff> createPayoff(const std::string& type, const double &K) const override;
    };
}

#endif //FACTORY_PAYOFF_DIGITAL_H
