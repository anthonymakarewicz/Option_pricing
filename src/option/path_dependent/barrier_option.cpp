#include "option/path_dependent/barrier_option.h"

namespace OptionPricer {

    // Base Barrier
    BarrierOption::~BarrierOption() = default;

    bool BarrierOption::isActive(const double &S) const {
        if (direction_ == BarrierDirection::Up) {
            return S >= B_;
        }
        return S <= B_; // BarrierDirection::Down
    }

    BarrierOption::BarrierOption(const std::string &ticker,
                                 std::unique_ptr<Payoff> payoff,
                                 const double &T,
                                 const double &B, BarrierDirection direction,
                                 std::shared_ptr<IMarketData> marketData)
    : PathDependentOption(ticker, std::move(payoff), T, std::move(marketData)),
        B_(B), direction_(direction) {}

    // Knock-In Barrier
    KnockInBarrierOption::~KnockInBarrierOption() = default;

    bool KnockInBarrierOption::isActive(const double &S) const {
        return BarrierOption::isActive(S);
    }

    double KnockInBarrierOption::calc_price() const {
        return 0.0;
    }

    // Knock-Out Barrier
    KnockOutBarrierOption::~KnockOutBarrierOption() = default;

    bool KnockOutBarrierOption::isActive(const double &S) const {
        return !BarrierOption::isActive(S);
    }

    double KnockOutBarrierOption::calc_price() const {
        return 0.0;
    }

}


