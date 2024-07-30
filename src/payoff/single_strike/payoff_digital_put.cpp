#include <algorithm>
#include "payoff/single_strike/payoff_digital_put.h"

namespace OptionPricer {
    PayoffDigitalPut::PayoffDigitalPut(const double &K) : PayoffDigital(K) {}

    PayoffDigitalPut::~PayoffDigitalPut() = default;

    double PayoffDigitalPut::operator()(const double &S) const {
        return K_ > S ? 1.0 : 0.0;
    }

    std::unique_ptr<Payoff> PayoffDigitalPut::clone() const {
        return std::make_unique<PayoffDigitalPut>(*this);
    }

    bool PayoffDigitalPut::compare(const Payoff &other) const {
        const auto otherPayoffPtr = dynamic_cast<const PayoffDigitalPut*>(&other);
        if (!otherPayoffPtr) return false;
        return K_ == otherPayoffPtr->K_;
    }
}