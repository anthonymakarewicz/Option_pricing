#include "option/path_dependent/asian/geometric_asian_option.h"

GeometricAsianOption::~GeometricAsianOption() = default;

double GeometricAsianOption::calc_price() const {
    return 0.0;
}

GeometricAsianOption::GeometricAsianOption(const std::string &ticker,
                                           std::unique_ptr<Payoff> payoff,
                                           const double &T)
: AsianOption(ticker, std::move(payoff), T) {}
