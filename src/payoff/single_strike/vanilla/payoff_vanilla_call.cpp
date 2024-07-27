#include <algorithm>
#include "payoff/single_strike/vanilla/payoff_vanilla_call.h"

PayoffVanillaCall::PayoffVanillaCall(const double &K) : PayoffVanilla(K) {}

PayoffVanillaCall::~PayoffVanillaCall() = default;

double PayoffVanillaCall::operator()(const double &S) const {
    return std::max(S - K_, 0.0);
}

std::unique_ptr<Payoff> PayoffVanillaCall::clone() const {
    return std::make_unique<PayoffVanillaCall>(*this);
}