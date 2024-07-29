#ifndef PAYOFF_VANILLA_CALL_H
#define PAYOFF_VANILLA_CALL_H

#include "base_payoff_vanilla.h"

namespace OptionPricer {
    class PayoffVanillaCall final : public PayoffVanilla {
    public:
        explicit PayoffVanillaCall(const double& K);
        ~PayoffVanillaCall() override;

        [[nodiscard]] std::unique_ptr<Payoff> clone() const override;
        bool operator==(const PayoffVanillaCall& other) const;
        bool operator!=(const PayoffVanillaCall& other) const;

        double operator()(const double& S) const override;
    };
}

#endif //PAYOFF_VANILLA_CALL_H
