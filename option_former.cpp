//
// Created by anthony on 18/02/2024.
//

#ifndef OPTION_PRICER_OPTION_CPP
#define OPTION_PRICER_OPTION_CPP

#include "option.h"


Option::Option(std::unique_ptr<Payoff> _payoff,
               const double& _T)
    : T(_T) {
    // Move the unique_ptr only after validating other parameters to avoid taking ownership if an exception is thrown
    if (_T < 0) throw std::invalid_argument("Time to expiration (T) must be positive.");
    // If all checks pass, then safely move the _payoff
    payoff = std::move(_payoff);
}

Option::~Option() {};

// other.payoff->clone() necessary because other.payoff is of type *Payoff which is abstract
Option::Option(const Option& other)
    : payoff(other.payoff ? other.payoff->clone() : nullptr),
    r(other.r), T(other.T), S(other.S), sigma(other.sigma) {}

Option& Option::operator=(const Option& other) {
    if (this != &other) {
        payoff = other.payoff ? other.payoff->clone() : nullptr;
        r = other.r;
        T = other.T;
        S = other.S;
        sigma = other.sigma;
    }
    return *this;
}


double Option::get_r() const {
    return r;
}

double Option::get_T() const {
    return T;
}

double Option::get_S() const {
    return S;
}

double Option::get_sigma() const {
    return sigma;
}

void Option::set_r(const double& _r) {
    if(_r < 0.0) {
        throw std::invalid_argument("r must be a positive number!");
    } else {
        r = _r;
    }
}

void Option::set_T(const double& _T) {
    if(_T < 0) {
        throw std::invalid_argument("T must be a positive number!");
    } else {
        T = _T;
    }
}

void Option::set_S(const double& _S) {
    if(_S < 0) {
        throw std::invalid_argument("S must be a positive number!");
    } else {
        S = _S;
    }
}

void Option::set_sigma(const double& _sigma) {
    if(_sigma < 0) {
        throw std::invalid_argument("sigma must be a positive number!");
    } else {
        sigma = _sigma;
    }
}

bool Option::operator==(const Option& rhs) const {
    return r == rhs.r &&
           T == rhs.T &&
           S == rhs.S &&
           sigma == rhs.sigma;
}

bool Option::operator!=(const Option& rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream& os, const Option& option) {
    os << " r: " << option.r << " T: " << option.T << " S: " << option.S << " sigma: "
       << option.sigma;
    return os;
}




#endif //OPTION_PRICER_OPTION_CPP