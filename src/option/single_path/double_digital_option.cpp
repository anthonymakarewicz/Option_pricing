#include "option/single_path/double_digital_option.h"

namespace OptionPricer {
    DoubleDigitalOption::~DoubleDigitalOption() = default;

    double DoubleDigitalOption::calc_price() const {
        return 0.0;
    }

    DoubleDigitalOption::DoubleDigitalOption(const std::string& ticker, std::unique_ptr<Payoff> payoff, const double& T,
        std::shared_ptr<IMarketData> marketData)
        : SinglePathOption(ticker, std::move(payoff), T, std::move(marketData)) {}
}