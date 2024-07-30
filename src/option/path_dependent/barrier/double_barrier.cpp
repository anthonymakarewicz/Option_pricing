#include "option/path_dependent/barrier/double_barrier.h"

namespace OptionPricer {
    DoubleBarrierOption::~DoubleBarrierOption() = default;

    double DoubleBarrierOption::calc_price() const {
        return 0.0;
    }

    DoubleBarrierOption::DoubleBarrierOption(const std::string &ticker, std::unique_ptr<Payoff> payoff, const double &T,
                                             std::shared_ptr<IMarketData> marketData,
                                             std::unique_ptr<KnockBehavior> knockBehavior,
                                             const double& lowerBarrier, const double& upperBarrier)
    : BarrierOption(ticker, std::move(payoff), T,
        std::move(marketData),
        std::move(knockBehavior)),
      lowerBarrier_(lowerBarrier), upperBarrier_(upperBarrier) {
        if (lowerBarrier_ >= upperBarrier_) {
            throw std::invalid_argument("Lower barrier must be less than upper barrier.");
        }
        if (lowerBarrier_ < 0 || upperBarrier_ < 0) {
            throw std::invalid_argument("Lower barrier and upper barrier must be positive.");
        }
    }

    bool DoubleBarrierOption::isOut(double S) const {
        return S < lowerBarrier_ || S > upperBarrier_;
    }
}