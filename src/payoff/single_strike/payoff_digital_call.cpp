#include <algorithm>
#include "payoff/single_strike/payoff_digital_call.h"

namespace OptionPricer {
    PayoffDigitalCall::PayoffDigitalCall(const double &K) : PayoffDigital(K) {}

    PayoffDigitalCall::~PayoffDigitalCall() = default;

    double PayoffDigitalCall::operator()(const double &S) const {
        return S > K_ ? 1.0 : 0.0;
    }

    std::unique_ptr<Payoff> PayoffDigitalCall::clone() const {
        return std::make_unique<PayoffDigitalCall>(*this);
    }

    bool PayoffDigitalCall::compare(const Payoff &other) const {
        const auto otherPayoffPtr = dynamic_cast<const PayoffDigitalCall*>(&other);
        if (!otherPayoffPtr) return false;
        return K_ == otherPayoffPtr->K_;
    }
}
