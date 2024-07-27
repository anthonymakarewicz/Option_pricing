#include "payoff/double_strikes/payoff_double_digital.h"

PayoffDoubleDigital::PayoffDoubleDigital(const double& K_L, const double& K_U)
: PayoffDoubleStrikes(K_L, K_U) {}

double PayoffDoubleDigital::operator()(const double& S) const {
    return S >= K_L_ && S <= K_U_ ? 1.0 : 0.0;
}

std::unique_ptr<Payoff> PayoffDoubleDigital::clone() const {
    return std::make_unique<PayoffDoubleDigital>(*this);
}