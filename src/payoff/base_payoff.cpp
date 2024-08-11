#include <ostream>
#include <typeinfo>
#include <cxxabi.h>

#include "payoff/base_payoff.h"

namespace OptionPricer {
    Payoff::Payoff(const PayoffType& type) : type_(type) {}

    Payoff::~Payoff() = default;

    PayoffType Payoff::getPayoffType() const {
        return type_;
    }

    void Payoff::print(std::ostream &os) const {
        os << "  -> Type: " << PayoffTypeToString(type_) << "\n";
    }

    bool Payoff::operator==(const Payoff &other) const {
        if (typeid(*this) != typeid(other)) return false;
        return this->compare(other) && other.compare(*this);
    }

    bool Payoff::operator!=(const Payoff &other) const {
        return !(*this == other);
    }

    std::ostream& operator<<(std::ostream& os, const Payoff& payoff) {
        payoff.print(os);
        return os;
    }

    double Payoff::operator()(const double &S) const {
        throw std::logic_error("Single-argument operator() should be overridden.");
    }

    double Payoff::operator()(const double &S, const double &extremeS) const {
        throw std::logic_error("Double-argument operator() should be overridden for Floating Strike Lookback.");
    }
}
