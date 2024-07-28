#include "option/path_dependent/asian/arithmetic_asian_option.h"

ArithmeticAsianOption::~ArithmeticAsianOption() = default;

double ArithmeticAsianOption::calc_price() const {
    return 0.0;
}

ArithmeticAsianOption::ArithmeticAsianOption(const std::string &ticker,
                                             std::unique_ptr<Payoff> payoff,
                                             const double &T)

: AsianOption(ticker, std::move(payoff), T) {}
