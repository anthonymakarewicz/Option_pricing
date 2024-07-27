#include <ostream>
#include <stdexcept>
#include "payoff/single_strike/base_payoff_single_strike.h"

PayoffSingleStrike::PayoffSingleStrike(const double& K) : K_(K) {
    if (K_ < 0) throw std::invalid_argument("Strike price (K) must be positive.");
}

PayoffSingleStrike::~PayoffSingleStrike() = default;

double PayoffSingleStrike::getK() const {
    return K_;
}

void PayoffSingleStrike::print(std::ostream &os) const {
    Payoff::print(os);
    os << "  -> Stike: " << K_ << "\n";
}