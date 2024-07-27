#ifndef PAYOFF_DIGITAL_CALL_H
#define PAYOFF_DIGITAL_CALL_H

#include "base_payoff_digital.h"

class PayoffDigitalCall final: public PayoffDigital {
public:
    explicit PayoffDigitalCall(const double& K);
    ~PayoffDigitalCall() override;

    double operator()(const double& S) const override;
    [[nodiscard]] std::unique_ptr<Payoff> clone() const override;
    bool operator==(const PayoffDigitalCall& other) const;
    bool operator!=(const PayoffDigitalCall& other) const;
};

#endif //PAYOFF_DIGITAL_CALL_H
