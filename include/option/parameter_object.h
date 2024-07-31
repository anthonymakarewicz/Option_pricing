#ifndef PARAMETER_OBJECT_H
#define PARAMETER_OBJECT_H

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <variant>

namespace OptionPricer {
    // ParameterObject class to hold various parameters
    class ParameterObject {
    public:
        using Parameter = std::variant<int, double, std::string>;

        void setParameter(const std::string& name, Parameter value);

        template <typename T>
        T getParameter(const std::string& name) const {
            if (!hasParameter(name)) {
                throw std::invalid_argument("Parameter not found: " + name);
            }

            try {
                return std::get<T>(parameters_.at(name));
            } catch (const std::bad_variant_access&) {
                throw std::invalid_argument("Parameter type mismatch for: " + name);
            }
        }

        [[nodiscard]] bool hasParameter(const std::string& name) const;

    private:
        std::unordered_map<std::string, Parameter> parameters_;
    };
}

#endif //PARAMETER_OBJECT_H
