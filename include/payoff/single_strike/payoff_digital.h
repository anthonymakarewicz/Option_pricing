#ifndef BASE_PAYOFF_DIGITAL_H
#define BASE_PAYOFF_DIGITAL_H

#include "base_payoff_single_strike.h"

namespace OptionPricer {
    // Abstract base class for PayoffDigital
    class PayoffDigital final: public PayoffSingleStrike {
    public:
        PayoffDigital(const PayoffType& type, const double& K);
        ~PayoffDigital() override;

        double operator()(const double& S) const override;
        [[nodiscard]] std::unique_ptr<Payoff> clone() const override;
        [[nodiscard]] bool compare(const Payoff &other) const override;
        std::string getType() const override;
    };

    /*
    class PayoffDigitalCall final: public PayoffDigital {
    public:
        explicit PayoffDigitalCall(const double& K);
        ~PayoffDigitalCall() override;

        double operator()(const double& S) const override;
        [[nodiscard]] std::unique_ptr<Payoff> clone() const override;
        [[nodiscard]] bool compare(const Payoff &other) const override;
    };


    class PayoffDigitalPut final: public PayoffDigital {
    public:
        explicit PayoffDigitalPut(const double& K);
        ~PayoffDigitalPut() override;

        double operator()(const double& S) const override;
        [[nodiscard]] std::unique_ptr<Payoff> clone() const override;
        [[nodiscard]] bool compare(const Payoff &other) const override;
    };
    */
}

#endif //BASE_PAYOFF_DIGITAL_H
