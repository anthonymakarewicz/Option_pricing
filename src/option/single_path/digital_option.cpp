#include "option/single_path/digital_option.h"

namespace OptionPricer {

    DigitalOption::~DigitalOption() = default;

    double DigitalOption::calc_price() const {
        return 0.0;
    }

    DigitalOption::DigitalOption(const std::string& ticker,
                                 std::unique_ptr<Payoff> payoff,
                                 const double& T,
                                 std::shared_ptr<IMarketData> marketData)
    : SinglePathOption(ticker, std::move(payoff), T, std::move(marketData)) {}

}