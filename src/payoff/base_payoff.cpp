#include <ostream>
#include <typeinfo>
#include <cxxabi.h>

#include "payoff/base_payoff.h"

namespace OptionPricer {
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
}