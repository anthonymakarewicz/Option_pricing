#ifndef RANDOM_NUMBER_GENERATOR_H
#define RANDOM_NUMBER_GENERATOR_H

#include "random/number_generator/base_generator.h"

namespace OptionPricer {

    class RNGenerator final: public NumberGenerarator {
    public:
        explicit RNGenerator(std::shared_ptr<Distribution> dist);
        RNGenerator(std::shared_ptr<Distribution> dist, const unsigned int& seed);

        [[nodiscard]] double generate(const int& step) override;

    private:
        std::mt19937 generator_; // Mersenne Twister PRNG
    };

}

#endif //RANDOM_NUMBER_GENERATOR_H
