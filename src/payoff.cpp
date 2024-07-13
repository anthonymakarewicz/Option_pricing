//
// Created by anthony on 18/02/2024.
//

#ifndef OPTION_PRICER_PAYOFF_CPP
#define OPTION_PRICER_PAYOFF_CPP

#include "payoff.h"

PayoffSingleStrike::PayoffSingleStrike(const double& K) : K_(K) {
    if (K_ < 0) throw std::invalid_argument("Strike price (K) must be positive.");
}
/*
std::unique_ptr<Payoff> PayoffSingleStrike::clone() const {
    return std::make_unique<PayoffSingleStrike>(this->K_);
}
*/

double PayoffSingleStrike::getK() const {
    return K_;
}


PayoffDoubleStrikes::PayoffDoubleStrikes(const double& K_L, const double& K_U)
    : K_L_(K_L), K_U_(K_U) {
    if (K_L_ < 0) throw std::invalid_argument("Lower Strike price (K_L) must be positive.");
    if (K_L_ < 0) throw std::invalid_argument("Upper Strike price (K_U) must be positive.");
}
/*
std::unique_ptr<Payoff> PayoffDoubleStrikes::clone() const {
    return std::make_unique<PayoffDoubleDigital>((*this).K_L_, (*this).K_U_);
}*/

double PayoffDoubleStrikes::getKU() const {
    return K_U_;
}

double PayoffDoubleStrikes::getKL() const {
    return K_L_;
}


// PayoffCall class
PayoffCall::PayoffCall(const double& K) : PayoffSingleStrike(K) {}

std::unique_ptr<Payoff> PayoffCall::clone() const {
    return std::make_unique<PayoffCall>(this->K_);
}

double PayoffCall::operator()(const double& S) const {
    return std::max(S - K_, 0.0);
}

// PayoffPut class
PayoffPut::PayoffPut(const double& K) : PayoffSingleStrike(K) {}

double PayoffPut::operator()(const double& S) const {
    return std::max(K_ - S, 0.0);
}


// PayoffDigitalCall class
PayoffDigitalCall::PayoffDigitalCall(const double& K) : PayoffSingleStrike(K) {}

double PayoffDigitalCall::operator()(const double& S) const {
    return S > K_ ? 1.0 : 0.0;
}

// PayoffDigitalPut class
PayoffDigitalPut::PayoffDigitalPut(const double& K) : PayoffSingleStrike(K) {}

double PayoffDigitalPut::operator()(const double& S) const {
    return K_ > S ? 1.0 : 0.0;
}


// PayoffDoubleDigitalCall class
PayoffDoubleDigital::PayoffDoubleDigital(const double& K_L, const double& K_U)
    : PayoffDoubleStrikes(K_L, K_U) {}

double PayoffDoubleDigital::operator()(const double& S) const {
    return S >= K_L_ && S <= K_U_ ? 1.0 : 0.0;
}


#endif //OPTION_PRICER_PAYOFF_CPP


