#include "random/number_generator/base_generator.h"

namespace OptionPricer {

    NumberGenerator::NumberGenerator(const unsigned int &dim)
    : dim_(dim) {
        std::random_device rd;
        seed_ = rd();
    }

    NumberGenerator::NumberGenerator(const unsigned int &dim, const unsigned int& seed)
    : dim_(dim), seed_(seed) {
        if (seed_ < 0) {
            throw std::invalid_argument("seed parameter must be a positive integer");
        }
    }

    NumberGenerator::~NumberGenerator() = default;

    unsigned int NumberGenerator::getDim() const {
        return dim_;
    }

    void NumberGenerator::validateDim() const {
        if (dim_ < 0) {
            throw std::invalid_argument("dim must be a positive integer");
        }
    }

}
