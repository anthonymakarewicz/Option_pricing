#include <algorithm>
#include "payoff/single_strike/payoff_vanilla_call.h"

PayoffVanillaCall::PayoffVanillaCall(const double &K) : PayoffVanilla(K) {}

PayoffVanillaCall::~PayoffVanillaCall() = default;

std::unique_ptr<Payoff> PayoffVanillaCall::clone() const {
    return std::make_unique<PayoffVanillaCall>(*this);
}

bool PayoffVanillaCall::operator==(const PayoffVanillaCall &other) const {
    return K_ == other.K_;
}

bool PayoffVanillaCall::operator!=(const PayoffVanillaCall &other) const {
    return !(*this == other);
}

double PayoffVanillaCall::operator()(const double &S) const {
    return std::max(S - K_, 0.0);
}
