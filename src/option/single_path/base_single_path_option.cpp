#include "option/single_path/base_single_path_option.h"

namespace OptionPricer {

    SinglePathOption::~SinglePathOption() = default;

    SinglePathOption::SinglePathOption(const std::string& ticker,
                                       std::unique_ptr<Payoff> payoff,
                                       const double& T,
                                       std::shared_ptr<IMarketData> marketData)
    : Option(ticker, std::move(payoff), T, std::move(marketData)) {}

}
