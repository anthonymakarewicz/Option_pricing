#include "option/path_dependent/american_option.h"

namespace OptionPricer {
    AmericanOption::~AmericanOption() = default;

    double AmericanOption::calc_price() const {
        return 0.0;
    }

    AmericanOption::AmericanOption(const std::string& ticker, std::unique_ptr<Payoff> payoff, const double& T)
    : PathDependentOption(ticker, std::move(payoff), T) {}
}
