#include "option/single_path/european_option.h"

namespace OptionPricer {
    EuropeanOption::~EuropeanOption() = default;

    double EuropeanOption::calc_price() const {
        return 0.0;
    }

    EuropeanOption::EuropeanOption(const std::string& ticker, std::unique_ptr<Payoff> payoff, const double &T,
        std::shared_ptr<IMarketData> marketData)
        : SinglePathOption(ticker, std::move(payoff), T, std::move(marketData)) {}
}