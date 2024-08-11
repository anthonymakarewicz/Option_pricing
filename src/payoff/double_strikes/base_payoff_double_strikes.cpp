#include <ostream>
#include <stdexcept>
#include "payoff/double_strikes/base_payoff_double_strikes.h"

namespace OptionPricer {
    PayoffDoubleStrikes::PayoffDoubleStrikes(const PayoffType& type, const double& K_L, const double& K_U)
        : Payoff(type), K_L_(K_L), K_U_(K_U) {
        if (K_L_ < 0) throw std::invalid_argument("Lower Strike price (K_L) must be positive.");
        if (K_U_ < 0) throw std::invalid_argument("Upper Strike price (K_U) must be positive.");
    }

    PayoffDoubleStrikes::~PayoffDoubleStrikes() = default;

    double PayoffDoubleStrikes::getKL() const {
        return K_L_;
    }

    double PayoffDoubleStrikes::getKU() const {
        return K_U_;
    }

    void PayoffDoubleStrikes::print(std::ostream &os) const {
        Payoff::print(os);
        os << "  -> Lower Strike: " << K_L_ << "\n";
        os << "  -> Upper Strike: " << K_U_ << "\n";
    }
}