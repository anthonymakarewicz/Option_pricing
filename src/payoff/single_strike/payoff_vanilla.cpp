#include <algorithm>
#include <string>
#include "payoff/single_strike/payoff_vanilla.h"

namespace OptionPricer {
    PayoffVanilla::PayoffVanilla(const PayoffType& type, const double &K) : PayoffSingleStrike(type, K) {
        if (type != PayoffType::Call && type != PayoffType::Put)
            throw std::invalid_argument("Invalid PayoffType for PayoffVanilla. Expected Call or Put.");
    }

    PayoffVanilla::~PayoffVanilla() = default;

    std::unique_ptr<Payoff> PayoffVanilla::clone() const {
        return std::make_unique<PayoffVanilla>(*this);
    }

    double PayoffVanilla::operator()(const double& S) const {
        if (type_ == PayoffType::Call) {
            return std::max(S - K_, 0.0);
        }
        return std::max(K_ - S, 0.0);
    }

    std::string PayoffVanilla::getType() const {
        return std::string("Vanilla ") + PayoffTypeToString(type_);
    }

    bool PayoffVanilla::compare(const Payoff &other) const {
        const auto otherPayoffPtr = dynamic_cast<const PayoffVanilla*>(&other);
        if (!otherPayoffPtr) return false;
        return type_ == otherPayoffPtr->type_ && K_ == otherPayoffPtr->K_;
    }


    /*
    // Vanilla Call
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

    // Vanilla Put
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
    */
}