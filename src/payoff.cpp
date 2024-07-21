#ifndef OPTION_PRICER_PAYOFF_CPP
#define OPTION_PRICER_PAYOFF_CPP

#include "payoff.h"
#include <ostream>
#include <stdexcept>
#include <typeinfo>
#include <cxxabi.h>

// Payoff abstract base class
std::string Payoff::getType() const {
    // Get the demangled name of the type
    int status;
    const char* mangledName = typeid(*this).name();
    char* demangledName = abi::__cxa_demangle(mangledName, nullptr, nullptr, &status);
    std::string typeName = (status == 0) ? demangledName : mangledName;
    std::free(demangledName);
    return typeName;
}

void Payoff::print(std::ostream &os) const {
    os << "Payoff: " << "\n";
    os << "-> Type: " << getType() << "\n";
}

std::ostream& operator<<(std::ostream& os, const Payoff& payoff) {
    payoff.print(os);
    return os;
}


// PayoffSingleStrike abstract class
PayoffSingleStrike::PayoffSingleStrike(const double& K) : K_(K) {
    if (K_ < 0) throw std::invalid_argument("Strike price (K) must be positive.");
}

double PayoffSingleStrike::getK() const {
    return K_;
}

void PayoffSingleStrike::print(std::ostream &os) const {
    Payoff::print(os);
    os << "-> Stike: " << K_ << "\n";
}


// PayoffDoubleStrikes abstract class
PayoffDoubleStrikes::PayoffDoubleStrikes(const double& K_L, const double& K_U)
    : K_L_(K_L), K_U_(K_U) {
    if (K_L_ < 0) throw std::invalid_argument("Lower Strike price (K_L) must be positive.");
    if (K_U_ < 0) throw std::invalid_argument("Upper Strike price (K_U) must be positive.");
}

void PayoffDoubleStrikes::print(std::ostream &os) const {
    Payoff::print(os);
    os << "-> Lower Strike: " << K_L_ << ", Upper Strike: " << K_U_;
}

double PayoffDoubleStrikes::getKU() const {
    return K_U_;
}

double PayoffDoubleStrikes::getKL() const {
    return K_L_;
}


// PayoffCall final class
PayoffCall::PayoffCall(const double& K) : PayoffSingleStrike(K) {}

std::unique_ptr<Payoff> PayoffCall::clone() const {
    return std::make_unique<PayoffCall>(K_);
}

double PayoffCall::operator()(const double& S) const {
    return std::max(S - K_, 0.0);
}

// PayoffPut final class
PayoffPut::PayoffPut(const double& K) : PayoffSingleStrike(K) {}

double PayoffPut::operator()(const double& S) const {
    return std::max(K_ - S, 0.0);
}

std::unique_ptr<Payoff> PayoffPut::clone() const {
    return std::make_unique<PayoffPut>(K_);
}


// PayoffDigitalCall  final class
PayoffDigitalCall::PayoffDigitalCall(const double& K) : PayoffSingleStrike(K) {}

double PayoffDigitalCall::operator()(const double& S) const {
    return S > K_ ? 1.0 : 0.0;
}

std::unique_ptr<Payoff> PayoffDigitalCall::clone() const {
    return std::make_unique<PayoffDigitalCall>(K_);
}

// PayoffDigitalPut final class
PayoffDigitalPut::PayoffDigitalPut(const double& K) : PayoffSingleStrike(K) {}

double PayoffDigitalPut::operator()(const double& S) const {
    return K_ > S ? 1.0 : 0.0;
}

std::unique_ptr<Payoff> PayoffDigitalPut::clone() const {
    return std::make_unique<PayoffDigitalPut>(K_);
}


// PayoffDoubleDigitalCall final class
PayoffDoubleDigital::PayoffDoubleDigital(const double& K_L, const double& K_U)
    : PayoffDoubleStrikes(K_L, K_U) {}

double PayoffDoubleDigital::operator()(const double& S) const {
    return S >= K_L_ && S <= K_U_ ? 1.0 : 0.0;
}

std::unique_ptr<Payoff> PayoffDoubleDigital::clone() const {
    return std::make_unique<PayoffDoubleDigital>(K_L_, K_U_);
}


#endif //OPTION_PRICER_PAYOFF_CPP