#ifndef PAYOFF_VANILLA_PUT_H
#define PAYOFF_VANILLA_PUT_H

#include "base_payoff_vanilla.h"

namespace OptionPricer {
    class PayoffVanillaPut final : public PayoffVanilla {
    public:
        explicit PayoffVanillaPut(const double& K);
        ~PayoffVanillaPut() override;

        [[nodiscard]] std::unique_ptr<Payoff> clone() const override;
        bool operator==(const PayoffVanillaPut& other) const;
        bool operator!=(const PayoffVanillaPut& other) const;

        double operator()(const double& S) const override;
    };
}

#endif //PAYOFF_VANILLA_PUT_H
