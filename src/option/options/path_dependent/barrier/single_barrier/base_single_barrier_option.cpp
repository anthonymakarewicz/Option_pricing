#include "option/options/path_dependent/barrier/single_barrier/base_single_barrier_option.h"

SingleBarrierOption::~SingleBarrierOption() = default;

SingleBarrierOption::SingleBarrierOption(const std::string &ticker, std::unique_ptr<Payoff> &&payoff, const double &T,
    std::unique_ptr<KnockBehavior> knockBehavior, const double &barrier)
        : BarrierOption(ticker, std::move(payoff), T, std::move(knockBehavior)),
          barrier_(barrier) {}