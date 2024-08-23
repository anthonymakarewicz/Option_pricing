#include "random/number_generator/pseudo_random_generator.h"

namespace OptionPricer {

    PseudoRandomNumberGenerator::~PseudoRandomNumberGenerator() = default;

    double PseudoRandomNumberGenerator::operator()(Distribution& dist) const {
        return dist(generator_);
    }

}

