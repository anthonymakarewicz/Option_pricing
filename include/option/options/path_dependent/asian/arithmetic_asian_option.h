#ifndef ARITHMETIC_ASIAN_OPTION_H
#define ARITHMETIC_ASIAN_OPTION_H

#include "base_asian_option.h"

class ArithmeticAsianOption final: public AsianOption {
public:
    ~ArithmeticAsianOption() override = default;
    [[nodiscard]] double calc_price() const override;

private:
    ArithmeticAsianOption(const std::string& ticker, std::unique_ptr<Payoff>&& payoff, const double& T);
    friend class PathDependentOptionFactory;
};

#endif //ARITHMETIC_ASIAN_OPTION_H