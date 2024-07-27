#ifndef PAYOFF_VANILLA_CALL_H
#define PAYOFF_VANILLA_CALL_H

#include "base_payoff_vanilla.h"

class PayoffVanillaCall final : public PayoffVanilla {
public:
    explicit PayoffVanillaCall(const double& K);
    ~PayoffVanillaCall() override;

    double operator()(const double& S) const override;
    [[nodiscard]] std::unique_ptr<Payoff> clone() const override;
};

#endif //PAYOFF_VANILLA_CALL_H
