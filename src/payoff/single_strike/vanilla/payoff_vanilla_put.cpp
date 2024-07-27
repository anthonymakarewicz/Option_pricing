#include <algorithm>
#include "payoff/single_strike/vanilla/payoff_vanilla_put.h"

PayoffVanillaPut::PayoffVanillaPut(const double &K) : PayoffVanilla(K) {}

PayoffVanillaPut::~PayoffVanillaPut() = default;

std::unique_ptr<Payoff> PayoffVanillaPut::clone() const {
    return std::make_unique<PayoffVanillaPut>(*this);
}

bool PayoffVanillaPut::operator==(const PayoffVanillaPut &other) const {
    return K_ == other.K_;
}

bool PayoffVanillaPut::operator!=(const PayoffVanillaPut &other) const {
    return !(*this == other);
}

double PayoffVanillaPut::operator()(const double &S) const {
    return std::max(K_ - S, 0.0);
}
