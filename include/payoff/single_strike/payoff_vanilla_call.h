#ifndef PAYOFF_VANILLA_CALL_H
#define PAYOFF_VANILLA_CALL_H

#include "base_payoff_vanilla.h"

namespace OptionPricer {
    class PayoffVanillaCall final : public PayoffVanilla {
    public:
        explicit PayoffVanillaCall(const double& K);
        ~PayoffVanillaCall() override;

        [[nodiscard]] std::unique_ptr<Payoff> clone() const override;
        double operator()(const double& S) const override;
        [[nodiscard]] bool compare(const Payoff &other) const override;
    };
}

#endif //PAYOFF_VANILLA_CALL_H
