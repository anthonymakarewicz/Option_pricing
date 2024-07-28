#ifndef BASE_PAYOFF_DIGITAL_H
#define BASE_PAYOFF_DIGITAL_H

#include "base_payoff_single_strike.h"

// Abastract base class for PayoffDigital
class PayoffDigital : public PayoffSingleStrike {
public:
    explicit PayoffDigital(const double& K);
    ~PayoffDigital() override;
};

#endif //BASE_PAYOFF_DIGITAL_H