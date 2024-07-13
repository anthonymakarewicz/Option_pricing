//
// Created by anthony on 18/02/2024.
//

#ifndef OPTION_PRICER_PAYOFF_CPP
#define OPTION_PRICER_PAYOFF_CPP

#include "payoff.h"

// Payoff abstract functor
Payoff::Payoff() {};
Payoff::~Payoff() {}


// PayoffCall class
PayoffCall::PayoffCall(const double& _K) : K(_K) {
    if (_K < 0) throw std::invalid_argument("Strike price (K) must be positive.");
}

PayoffCall::~PayoffCall() {}

std::unique_ptr<Payoff> PayoffCall::clone() const {
return std::make_unique<PayoffCall>((*this).K);
}

double PayoffCall::operator()(const double& S) const {
    return std::max(S-K, 0.0);
}

// PayoffPut class
PayoffPut::PayoffPut(const double& _K) : K(_K) {
    if (_K < 0) throw std::invalid_argument("Strike price (K) must be positive.");
}

PayoffPut::~PayoffPut() {}

std::unique_ptr<Payoff> PayoffPut::clone() const {
    return std::make_unique<PayoffPut>((*this).K);
}

double PayoffPut::operator()(const double& S) const {
    return std::max(K-S, 0.0);
}

// PayoffDigitalCall class
PayoffDigitalCall::PayoffDigitalCall(const double& _K) : K(_K) {
    if (_K < 0) throw std::invalid_argument("Strike price (K) must be positive.");
}

PayoffDigitalCall::~PayoffDigitalCall() {}

std::unique_ptr<Payoff> PayoffDigitalCall::clone() const {
    return std::make_unique<PayoffDigitalCall>((*this).K);
}

double PayoffDigitalCall::operator()(const double& S) const {
    return S > K ? 1.0 : 0.0;
}

// PayoffDigitalPut class
PayoffDigitalPut::PayoffDigitalPut(const double& _K) : K(_K) {
    if (_K < 0) throw std::invalid_argument("Strike price (K) must be positive.");
}

PayoffDigitalPut::~PayoffDigitalPut() {}

std::unique_ptr<Payoff> PayoffDigitalPut::clone() const {
    return std::make_unique<PayoffDigitalPut>((*this).K);
}

double PayoffDigitalPut::operator()(const double& S) const {
    return K > S ? 1.0 : 0.0;
}


// PayoffDoubleDigitalCall class
PayoffDoubleDigital::PayoffDoubleDigital(const double& _K_L, const double& _K_U)
    : K_L(_K_L), K_U(_K_U) {
    if (_K_L < 0) throw std::invalid_argument("Lower Strike price (K_L) must be positive.");
    if (_K_L < 0) throw std::invalid_argument("Upper Strike price (K_U) must be positive.");
}

PayoffDoubleDigital::~PayoffDoubleDigital() {}

std::unique_ptr<Payoff> PayoffDoubleDigital::clone() const {
    return std::make_unique<PayoffDoubleDigital>((*this).K_L, (*this).K_U);
}

double PayoffDoubleDigital::operator()(const double& S) const {
    return S >= K_L && S <= K_U ? 1.0 : 0.0;
}



#endif //OPTION_PRICER_PAYOFF_CPP


