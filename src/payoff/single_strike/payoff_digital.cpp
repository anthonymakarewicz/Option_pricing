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

}
