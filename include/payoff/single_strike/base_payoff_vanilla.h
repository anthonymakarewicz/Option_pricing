#ifndef BASE_PAYOFF_VANILLA_H
#define BASE_PAYOFF_VANILLA_H

#include "base_payoff_single_strike.h"

// Abastract base class for PayoffVanilla
class PayoffVanilla : public PayoffSingleStrike {
public:
    explicit PayoffVanilla(const double& K);
    ~PayoffVanilla() override;
};

#endif //BASE_PAYOFF_VANILLA_H
