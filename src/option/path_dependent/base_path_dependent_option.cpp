#include "option/path_dependent/base_path_dependent_option.h"

namespace OptionPricer {
    PathDependentOption::~PathDependentOption() = default;

    PathDependentOption::PathDependentOption(const std::string& ticker,
                                             std::unique_ptr<Payoff> payoff,
                                             const double& T,
                                             std::shared_ptr<IMarketData> marketData)
    : Option(ticker, std::move(payoff), T, std::move(marketData)) {}
}