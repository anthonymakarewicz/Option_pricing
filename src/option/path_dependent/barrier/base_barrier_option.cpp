#include "option/path_dependent/barrier/base_barrier_option.h"

namespace OptionPricer {
    BarrierOption::~BarrierOption() = default;

    double BarrierOption::payoff(double S) const {
        if (!isActive(S)) {
            return 0.0;
        }
        return Option::payoff();
    }

    BarrierOption::BarrierOption(const std::string &ticker, std::unique_ptr<Payoff> payoff, const double &T,
        std::shared_ptr<IMarketData> marketData, std::unique_ptr<KnockBehavior> knockBehavior)
    : PathDependentOption(ticker, std::move(payoff), T, std::move(marketData)),
      knockBehavior_(std::move(knockBehavior)) {}

    bool BarrierOption::isActive(double S) const {
        return knockBehavior_->isActive(isOut(S));
    }
}
