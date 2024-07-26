#include "option/options/single_path/digital/digital_option.h"

DigitalOption::~DigitalOption() = default;

double DigitalOption::calc_price() const {
    return 0.0;
}

DigitalOption::DigitalOption(const std::string& ticker, std::unique_ptr<Payoff>&& payoff, const double& T)
    : SinglePathOption(ticker, std::move(payoff), T) {}