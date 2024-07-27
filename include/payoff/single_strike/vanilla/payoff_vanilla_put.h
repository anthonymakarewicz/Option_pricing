#ifndef PAYOFF_VANILLA_PUT_H
#define PAYOFF_VANILLA_PUT_H

#include "base_payoff_vanilla.h"

class PayoffVanillaPut final : public PayoffVanilla {
public:
    explicit PayoffVanillaPut(const double& K);
    ~PayoffVanillaPut() override;

    double operator()(const double& S) const override;
    [[nodiscard]] std::unique_ptr<Payoff> clone() const override;
};

#endif //PAYOFF_VANILLA_PUT_H
