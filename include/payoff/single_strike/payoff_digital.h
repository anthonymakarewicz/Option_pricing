#ifndef BASE_PAYOFF_DIGITAL_H
#define BASE_PAYOFF_DIGITAL_H

#include "base_payoff_single_strike.h"

namespace OptionPricer {

    class PayoffDigital final: public PayoffSingleStrike {
    public:
        PayoffDigital(const PayoffType& type, const double& K);
        ~PayoffDigital() override;

        std::string getType() const override;
        [[nodiscard]] std::unique_ptr<Payoff> clone() const override;
        double operator()(const double& S) const override;
        [[nodiscard]] bool compare(const Payoff &other) const override;
    };

}

#endif //BASE_PAYOFF_DIGITAL_H
