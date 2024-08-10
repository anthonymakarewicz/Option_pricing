#include <algorithm>
#include "payoff/single_strike/payoff_vanilla_call.h"

namespace OptionPricer {
    PayoffVanillaCall::PayoffVanillaCall(const double &K) : PayoffVanilla(K) {}

    PayoffVanillaCall::~PayoffVanillaCall() = default;

    std::unique_ptr<Payoff> PayoffVanillaCall::clone() const {
        return std::make_unique<PayoffVanillaCall>(*this);
    }

    double PayoffVanillaCall::operator()(const double &S) const {
        return std::max(S - K_, 0.0);
    }

    bool PayoffVanillaCall::compare(const Payoff &other) const {
        const auto otherPayoffPtr = dynamic_cast<const PayoffVanillaCall*>(&other);
        if (!otherPayoffPtr) return false;
        return K_ == otherPayoffPtr->K_;
    }
}
