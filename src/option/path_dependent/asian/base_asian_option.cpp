#include "option/path_dependent/asian/base_asian_option.h"

namespace OptionPricer {
    AsianOption::~AsianOption() = default;

    AsianOption::AsianOption(const std::string &ticker, std::unique_ptr<Payoff> payoff, const double &T,
        std::shared_ptr<IMarketData> marketData)
    : PathDependentOption(ticker, std::move(payoff), T, std::move(marketData)) {}
}
