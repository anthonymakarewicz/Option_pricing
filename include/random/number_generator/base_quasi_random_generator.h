#ifndef BASE_QUASI_RANDOM_GENERATOR_H
#define BASE_QUASI_RANDOM_GENERATOR_H

#include "random/number_generator/base_generator.h"

namespace OptionPricer {

    class QuasiRandomNumberGenerator : public NumberGenerator {
    public:
        explicit QuasiRandomNumberGenerator(const unsigned int& dim);
        QuasiRandomNumberGenerator(const unsigned int& dim, const unsigned int& seed);

        ~QuasiRandomNumberGenerator() override;

    protected:
        mutable int step_;
        mutable std::vector<double> point_; // Maybe use array
    };

}

#endif //BASE_QUASI_RANDOM_GENERATOR_H
