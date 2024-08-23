#include "random/number_generator/base_quasi_random_generator.h"

namespace OptionPricer {

    QuasiRandomNumberGenerator::QuasiRandomNumberGenerator(const unsigned int &dim)
    : NumberGenerator(dim), step_(0), point_(dim_){
        validateDim();
    }

    QuasiRandomNumberGenerator::QuasiRandomNumberGenerator(const unsigned int &dim, const unsigned int &seed)
    : NumberGenerator(dim, seed), step_(0), point_(dim_) {
        validateDim();
    }

    QuasiRandomNumberGenerator::~QuasiRandomNumberGenerator() = default;

}
