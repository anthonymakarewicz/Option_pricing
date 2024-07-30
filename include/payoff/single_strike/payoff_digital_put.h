#ifndef PAYOFF_DIGITAL_PUT_H
#define PAYOFF_DIGITAL_PUT_H

#include "base_payoff_digital.h"

namespace OptionPricer {
    class PayoffDigitalPut final: public PayoffDigital {
    public:
        explicit PayoffDigitalPut(const double& K);
        ~PayoffDigitalPut() override;

        double operator()(const double& S) const override;
        [[nodiscard]] std::unique_ptr<Payoff> clone() const override;
        [[nodiscard]] bool compare(const Payoff &other) const override;
    };
}

#endif //PAYOFF_DIGITAL_PUT_H
