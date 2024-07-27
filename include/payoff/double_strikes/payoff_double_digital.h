#ifndef PAYOFF_DOUBLE_DIGITAL_H
#define PAYOFF_DOUBLE_DIGITAL_H

#include "base_payoff_double_strikes.h"

// DoubleDigital options are both call and put
class PayoffDoubleDigital final: public PayoffDoubleStrikes {
public:
    PayoffDoubleDigital(const double& K_L, const double& K_U);
    ~PayoffDoubleDigital() override;

    double operator()(const double& S) const override;
    [[nodiscard]] std::unique_ptr<Payoff> clone() const override;
};

#endif //PAYOFF_DOUBLE_DIGITAL_H