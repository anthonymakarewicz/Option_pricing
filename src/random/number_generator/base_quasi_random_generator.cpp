#include "random/number_generator/base_quasi_random_generator.h"

namespace OptionPricer {

    QuasiRandomNumberGenerator::QuasiRandomNumberGenerator(std::shared_ptr<Distribution> dist,
                                                           const unsigned int &dim)
    : NumberGenerator(std::move(dist)), dim_(dim), point_(dim_) {
        validateDim();
    }

    QuasiRandomNumberGenerator::QuasiRandomNumberGenerator(std::shared_ptr<Distribution> dist,
                                                           const unsigned int &seed,
                                                           const unsigned int &dim)
    : NumberGenerator(std::move(dist), seed), dim_(dim), point_(dim_) {
        validateDim();
    }

    QuasiRandomNumberGenerator::~QuasiRandomNumberGenerator() = default;

    unsigned int QuasiRandomNumberGenerator::getDim() const {
        return dim_;
    }

    void QuasiRandomNumberGenerator::validateDim() const {
        if (dim_ < 0) {
            throw std::invalid_argument("dim must be a positive integer");
        }
    }

}
