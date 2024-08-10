#include "option/parameter_object.h"

namespace OptionPricer {
    void ParameterObject::setParameter(const std::string &name, Parameter value) {
        parameters_[name] = std::move(value);
    }

    bool ParameterObject::hasParameter(const std::string &name) const {
        // Introduced in C++20 for less verbosity than find()
        return parameters_.contains(name);
    }

}


