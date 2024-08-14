#ifndef BASE_PAYOFF_VANILLA_H
#define BASE_PAYOFF_VANILLA_H

#include "base_payoff_single_strike.h"

namespace OptionPricer {

    class PayoffVanilla final: public PayoffSingleStrike {
    public:
        PayoffVanilla(const PayoffType& type, const double& K);
        ~PayoffVanilla() override;

        [[nodiscard]] std::unique_ptr<Payoff> clone() const override;
        double operator()(const double& S) const override;
        std::string getType() const override;
        [[nodiscard]] bool compare(const Payoff &other) const override;
    };

}

#endif //BASE_PAYOFF_VANILLA_H
