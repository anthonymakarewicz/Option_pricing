#ifndef FACTORY_PAYOFF_DOUBLE_DIGITAL_H
#define FACTORY_PAYOFF_DOUBLE_DIGITAL_H

#include "payoff/double_strikes/factory_payoff_double_strikes.h"

namespace OptionPricer {
    class PayoffDoubleDigitalFactory final: public PayoffDoubleStrikesFactory {
    public:
        [[nodiscard]] std::unique_ptr<Payoff> createPayoff(const std::string& type,
            const double& K1, const double& K2) const override;
    };
}




#endif //FACTORY_PAYOFF_DOUBLE_DIGITAL_H
