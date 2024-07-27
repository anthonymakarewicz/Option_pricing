#include <ostream>
#include <typeinfo>
#include <cxxabi.h>

#include "payoff/base_payoff.h"

Payoff::Payoff() = default;

Payoff::~Payoff() = default;

std::string Payoff::getType() const {
    int status;
    const char* mangledName = typeid(*this).name();
    char* demangledName = abi::__cxa_demangle(mangledName, nullptr, nullptr, &status);
    std::string typeName = (status == 0) ? demangledName : mangledName;
    std::free(demangledName);
    return typeName;
}

void Payoff::print(std::ostream &os) const {
    os << "  -> Type: " << getType() << "\n";
}

std::ostream& operator<<(std::ostream& os, const Payoff& payoff) {
    payoff.print(os);
    return os;
}