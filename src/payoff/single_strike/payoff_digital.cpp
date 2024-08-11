#include <algorithm>
#include <string>
#include "payoff/single_strike/payoff_digital.h"

namespace OptionPricer {
    PayoffDigital::PayoffDigital(const PayoffType& type, const double &K) : PayoffSingleStrike(type, K) {
        if (type != PayoffType::Call && type != PayoffType::Put)
            throw std::invalid_argument("Invalid PayoffType for PayoffVanilla. Expected Call or Put.");
    }

    PayoffDigital::~PayoffDigital() = default;

    std::unique_ptr<Payoff> PayoffDigital::clone() const {
        return std::make_unique<PayoffDigital>(*this);
    }

    double PayoffDigital::operator()(const double& S) const {
        if (type_ == PayoffType::Call) {
            return S > K_ ? 1.0 : 0.0;
        }
        return K_ > S ? 1.0 : 0.0;
    }

    std::string PayoffDigital::getType() const {
        return std::string("Digital ") + PayoffTypeToString(type_);
    }

    bool PayoffDigital::compare(const Payoff &other) const {
        const auto otherPayoffPtr = dynamic_cast<const PayoffDigital*>(&other);
        if (!otherPayoffPtr) return false;
        return type_ == otherPayoffPtr->type_ && K_ == otherPayoffPtr->K_;
    }

    /*
    // Digital Call
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

    // Digital Put
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
    */
}
