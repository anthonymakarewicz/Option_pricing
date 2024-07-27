#ifndef BASE_PAYOFF_DOUBLE_STRIKES_H
#define BASE_PAYOFF_DOUBLE_STRIKES_H

#include "../base_payoff.h"

// Abastract base class for PayoffDoubleStrikes
class PayoffDoubleStrikes : public Payoff {
public:
    PayoffDoubleStrikes(const double& K_L, const double& K_U);
    ~PayoffDoubleStrikes() override;

    [[nodiscard]] double getKL() const;
    [[nodiscard]] double getKU() const;
    void print(std::ostream& os) const override;

protected:
    double K_L_;
    double K_U_;
};

#endif //BASE_PAYOFF_DOUBLE_STRIKES_H
