#include "option/options/path_dependent/barrier/base_barrier_option.h"

BarrierOption::~BarrierOption() = default;

double BarrierOption::payoff(double S) const {
    if (!isActive(S)) {
        return 0.0;
    }
    return Option::payoff(S);
}

BarrierOption::BarrierOption(const std::string &ticker, std::unique_ptr<Payoff> payoff, const double &T,
    std::unique_ptr<KnockBehavior> knockBehavior)
: PathDependentOption(ticker, std::move(payoff), T) {}