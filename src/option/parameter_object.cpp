#include "option/parameter_object.h"

namespace OptionPricer {
    void ParameterObject::setParameter(const std::string &name, Parameter value) {
        parameters_[name] = std::move(value);
    }

    bool ParameterObject::hasParameter(const std::string &name) const {
        return parameters_.find(name) != parameters_.end();
    }

}


