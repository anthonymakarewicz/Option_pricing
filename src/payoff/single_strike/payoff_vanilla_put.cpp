#include <algorithm>
#include "payoff/single_strike/payoff_vanilla_put.h"

namespace OptionPricer {
    PayoffVanillaPut::PayoffVanillaPut(const double &K) : PayoffVanilla(K) {}

    PayoffVanillaPut::~PayoffVanillaPut() = default;

    std::unique_ptr<Payoff> PayoffVanillaPut::clone() const {
        return std::make_unique<PayoffVanillaPut>(*this);
    }

    double PayoffVanillaPut::operator()(const double &S) const {
        return std::max(K_ - S, 0.0);
    }

    bool PayoffVanillaPut::compare(const Payoff &other) const {
        const auto otherPayoffPtr = dynamic_cast<const PayoffVanillaPut*>(&other);
        if (!otherPayoffPtr) return false;
        return K_ == otherPayoffPtr->K_;
    }
}
