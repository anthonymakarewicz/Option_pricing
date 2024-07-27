#include <algorithm>
#include "payoff/single_strike/digital/payoff_digital_call.h"

PayoffDigitalCall::PayoffDigitalCall(const double &K) : PayoffDigital(K) {}

PayoffDigitalCall::~PayoffDigitalCall() = default;

double PayoffDigitalCall::operator()(const double &S) const {
    return S > K_ ? 1.0 : 0.0;
}

std::unique_ptr<Payoff> PayoffDigitalCall::clone() const {
    return std::make_unique<PayoffDigitalCall>(*this);
}

bool PayoffDigitalCall::operator==(const PayoffDigitalCall &other) const {
    return K_ == other.K_;
}

bool PayoffDigitalCall::operator!=(const PayoffDigitalCall &other) const {
    return !(*this == other);
}
