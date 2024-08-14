#ifndef PAYOFFF_FLOATING_STRIKE_LOOKBACK_H
#define PAYOFFF_FLOATING_STRIKE_LOOKBACK_H

#include "payoff/base_payoff.h"

namespace OptionPricer {

    class PayoffLookbackFloatingStrike final: public Payoff {
    public:
        explicit PayoffLookbackFloatingStrike(const PayoffType& type);
        ~PayoffLookbackFloatingStrike() override;

        std::string getType() const override;
        [[nodiscard]] std::unique_ptr<Payoff> clone() const override;
        double operator()(const double& S, const double& extremeS) const override;
        [[nodiscard]] bool compare(const Payoff& other) const override;
    };

}

#endif //PAYOFFF_FLOATING_STRIKE_LOOKBACK_H
