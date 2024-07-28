#include "option/path_dependent/barrier/up_single_barrier_option.h"

UpSingleBarrierOption::~UpSingleBarrierOption() = default;

double UpSingleBarrierOption::calc_price() const {
    return 0.0;
}

UpSingleBarrierOption::UpSingleBarrierOption(const std::string &ticker, std::unique_ptr<Payoff> payoff,
    const double &T, std::unique_ptr<KnockBehavior> knockBehavior, const double &barrier)
: SingleBarrierOption(ticker, std::move(payoff), T, std::move(knockBehavior), barrier) {}

bool UpSingleBarrierOption::isOut(double S) const {
    return S > barrier_;
}