#include <algorithm>
#include "payoff/single_strike/digital/payoff_digital_put.h"

PayoffDigitalPut::PayoffDigitalPut(const double &K) : PayoffDigital(K) {}

PayoffDigitalPut::~PayoffDigitalPut() = default;

double PayoffDigitalPut::operator()(const double &S) const {
    return K_ > S ? 1.0 : 0.0;
}

std::unique_ptr<Payoff> PayoffDigitalPut::clone() const {
    return std::make_unique<PayoffDigitalPut>(*this);
}

bool PayoffDigitalPut::operator==(const PayoffDigitalPut &other) const {
    return K_ == other.K_;
}

bool PayoffDigitalPut::operator!=(const PayoffDigitalPut &other) const {
    return !(*this == other);
}