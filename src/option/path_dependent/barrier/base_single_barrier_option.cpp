#include "option/path_dependent/barrier/base_single_barrier_option.h"

namespace OptionPricer {
SingleBarrierOption::~SingleBarrierOption() = default;

SingleBarrierOption::SingleBarrierOption(const std::string &ticker, std::unique_ptr<Payoff> payoff, const double &T,
                                         std::shared_ptr<IMarketData> marketData,
                                         std::unique_ptr<KnockBehavior> knockBehavior, const double &barrier)
    : BarrierOption(ticker, std::move(payoff), T, std::move(marketData),
        std::move(knockBehavior)),
          barrier_(barrier) {}
}