#ifndef PAYOFF_DOUBLE_DIGITAL_H
#define PAYOFF_DOUBLE_DIGITAL_H

#include "base_payoff_double_strikes.h"

namespace OptionPricer {
    // DoubleDigital options are both call and put
    class PayoffDoubleDigital final: public PayoffDoubleStrikes {
    public:
        PayoffDoubleDigital(const double& K_L, const double& K_U);
        ~PayoffDoubleDigital() override;

        [[nodiscard]] std::unique_ptr<Payoff> clone() const override;
        bool operator==(const PayoffDoubleDigital& other) const;
        bool operator!=(const PayoffDoubleDigital& other) const;

        double operator()(const double& S) const override;
    };
}

#endif //PAYOFF_DOUBLE_DIGITAL_H