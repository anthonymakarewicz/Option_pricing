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

    /*
    class PayoffVanillaCall final : public PayoffVanilla {
    public:
        explicit PayoffVanillaCall(const double& K);
        ~PayoffVanillaCall() override;

        [[nodiscard]] std::unique_ptr<Payoff> clone() const override;
        double operator()(const double& S) const override;
        [[nodiscard]] bool compare(const Payoff &other) const override;
    };


    class PayoffVanillaPut final : public PayoffVanilla {
    public:
        explicit PayoffVanillaPut(const double& K);
        ~PayoffVanillaPut() override;

        [[nodiscard]] std::unique_ptr<Payoff> clone() const override;

        double operator()(const double& S) const override;
        [[nodiscard]] bool compare(const Payoff &other) const override;
    };
    */
}

#endif //BASE_PAYOFF_VANILLA_H
