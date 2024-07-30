#include "option/path_dependent/barrier/down_single_barrier_option.h"

namespace OptionPricer {
    DownSingleBarrierOption::~DownSingleBarrierOption() = default;

    double DownSingleBarrierOption::calc_price() const {
        return 0.0;
    }

    DownSingleBarrierOption::DownSingleBarrierOption(const std::string &ticker, std::unique_ptr<Payoff> payoff,
        const double &T, std::shared_ptr<IMarketData> marketData, std::unique_ptr<KnockBehavior> knockBehavior,
        const double &barrier)
    : SingleBarrierOption(ticker, std::move(payoff),T, std::move(marketData),
        std::move(knockBehavior), barrier) {}

    bool DownSingleBarrierOption::isOut(double S) const {
        return S < barrier_;
    }
}