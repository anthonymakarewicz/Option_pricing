#ifndef GEOMETRIC_ASIAN_OPTION_H
#define GEOMETRIC_ASIAN_OPTION_H

#include "base_asian_option.h"

class GeometricAsianOption final: public AsianOption {
public:
    ~GeometricAsianOption() override;
    [[nodiscard]] double calc_price() const override;

private:
    GeometricAsianOption(const std::string& ticker, std::unique_ptr<Payoff>&& payoff, const double& T);
};

#endif //GEOMETRIC_ASIAN_OPTION_H
