#include "random/number_generator/random_generator.h"

namespace OptionPricer {

    RandomNumberGenerator::RandomNumberGenerator(std::shared_ptr<Distribution> dist)
    : NumberGenerator(std::move(dist)), generator_(seed_) {}

    RandomNumberGenerator::RandomNumberGenerator(std::shared_ptr<Distribution> dist, const unsigned int &seed)
    : NumberGenerator(std::move(dist), seed), generator_(seed_) {}

    double RandomNumberGenerator::generate(const int &step) {
        return (*dist_)(generator_);
    }

}
