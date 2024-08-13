#include <string>
#include "payoff/double_strikes/payoff_double_digital.h"

namespace OptionPricer {

    PayoffDoubleDigital::PayoffDoubleDigital(const double& K_L, const double& K_U)
    : PayoffDoubleStrikes(PayoffType::DoubleDigital, K_L, K_U) {}

    PayoffDoubleDigital::~PayoffDoubleDigital() = default;

    std::unique_ptr<Payoff> PayoffDoubleDigital::clone() const {
        return std::make_unique<PayoffDoubleDigital>(*this);
    }

    double PayoffDoubleDigital::operator()(const double& S) const {
        return  K_L_ <= S && S <= K_U_ ? 1.0 : 0.0;
    }

    bool PayoffDoubleDigital::compare(const Payoff &other) const {
        const auto otherPayoffPtr = dynamic_cast<const PayoffDoubleDigital*>(&other);
        if (!otherPayoffPtr) return false;
        return K_U_ == otherPayoffPtr->K_U_ && K_L_ == otherPayoffPtr->K_L_;
    }

    std::string PayoffDoubleDigital::getType() const {
        return {"Double Digital"};
    }

}