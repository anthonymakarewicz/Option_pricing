#ifndef PSEUDO_RANDOM_NUMBER_GENERATOR_H
#define PSEUDO_RANDOM_NUMBER_GENERATOR_H

#include "random/number_generator/base_generator.h"

namespace OptionPricer {

    class PseudoRandomNumberGenerator final: public NumberGenerator {
    public:
        using NumberGenerator::NumberGenerator;
        ~PseudoRandomNumberGenerator() override;

        double operator()(Distribution& dist) const override;

    private:
        mutable std::mt19937 generator_; // Mersenne Twister PRNG
    };

}

#endif //PSEUDO_RANDOM_NUMBER_GENERATOR_H
