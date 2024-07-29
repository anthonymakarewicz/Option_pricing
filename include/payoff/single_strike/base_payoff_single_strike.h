#ifndef BASE_PAYOFF_SINGLE_STRIKE_H
#define BASE_PAYOFF_SINGLE_STRIKE_H

#include "../base_payoff.h"

namespace OptionPricer {
    // Abastract base class for PayoffSingleStrike
    class PayoffSingleStrike : public Payoff {
    public:
        explicit PayoffSingleStrike(const double& K);
        ~PayoffSingleStrike() override;

        [[nodiscard]] double getK() const;
        void print(std::ostream& os) const override;

    protected:
        double K_;
    };
}

#endif //BASE_PAYOFF_SINGLE_STRIKE_H
