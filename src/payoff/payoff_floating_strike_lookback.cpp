#include "payoff/payoff_floating_strike_lookback.h"

namespace OptionPricer {

    PayoffLookbackFloatingStrike::PayoffLookbackFloatingStrike(const PayoffType& type)
        : Payoff(type) {
        if (type != PayoffType::Call && type != PayoffType::Put)
            throw std::invalid_argument("Invalid PayoffType for Floating Strike Lookback."
                                        " Expected Call or Put.");
    }

    PayoffLookbackFloatingStrike::~PayoffLookbackFloatingStrike() = default;

    std::string PayoffLookbackFloatingStrike::getType() const {
        return std::string("Floating Strike Lookback ") + PayoffTypeToString(type_);
    }

    std::unique_ptr<Payoff> PayoffLookbackFloatingStrike::clone() const {
        return std::make_unique<PayoffLookbackFloatingStrike>(*this);
    }

    double PayoffLookbackFloatingStrike::operator()(const double& S, const double& extremeS) const {
        if (type_ == PayoffType::Call) {
            return std::max(S - extremeS, 0.0); // max(S_T - S_min, 0)
        }
        return std::max(extremeS - S, 0.0); // max(S_max - S_T, 0)
    }

    bool PayoffLookbackFloatingStrike::compare(const Payoff& other) const {
        const auto* otherPayoffPtr = dynamic_cast<const PayoffLookbackFloatingStrike*>(&other);
        return otherPayoffPtr && type_ == otherPayoffPtr->type_;
    }

}
