#ifndef AMERICAN_OPTION_H
#define AMERICAN_OPTION_H

#include "base_path_dependent_option.h"

class AmericanOption final: public PathDependentOption {
public:
    ~AmericanOption() override = default;
    [[nodiscard]] double calc_price() const override;

private:
    AmericanOption(const std::string& ticker, std::unique_ptr<Payoff>&& payoff, const double& T);
    friend class AmericanOptionFactory;
};

#endif //AMERICAN_OPTION_H
