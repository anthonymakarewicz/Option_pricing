#include "option/options/path_dependent/asian/base_asian_option.h"

AsianOption::~AsianOption() = default;

AsianOption::AsianOption(const std::string &ticker, std::unique_ptr<Payoff> &&payoff, const double &T)
: PathDependentOption(ticker, std::move(payoff), T) {}
