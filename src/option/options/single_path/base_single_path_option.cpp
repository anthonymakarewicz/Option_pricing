#include "option/options/single_path/base_single_path_option.h"

SinglePathOption::~SinglePathOption() = default;

SinglePathOption::SinglePathOption(const std::string& ticker, std::unique_ptr<Payoff> payoff, const double& T)
    : Option(ticker, std::move(payoff), T) {}