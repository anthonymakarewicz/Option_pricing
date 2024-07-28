#include "payoff/double_strikes/payoff_double_digital.h"

PayoffDoubleDigital::PayoffDoubleDigital(const double& K_L, const double& K_U)
: PayoffDoubleStrikes(K_L, K_U) {}

PayoffDoubleDigital::~PayoffDoubleDigital() = default;

std::unique_ptr<Payoff> PayoffDoubleDigital::clone() const {
    return std::make_unique<PayoffDoubleDigital>(*this);
}

bool PayoffDoubleDigital::operator==(const PayoffDoubleDigital &other) const {
    return (K_L_ == other.K_L_) && (K_U_ == other.K_U_);
}

bool PayoffDoubleDigital::operator!=(const PayoffDoubleDigital &other) const {
    return !(*this == other);
}

double PayoffDoubleDigital::operator()(const double& S) const {
    return  K_L_ <= S && S <= K_U_ ? 1.0 : 0.0;
}