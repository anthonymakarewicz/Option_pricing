#include "random/number_generator/random_generator.h"

namespace OptionPricer {

    RNGenerator::RNGenerator(std::shared_ptr<Distribution> dist)
    : NumberGenerarator(std::move(dist)), generator_(seed_) {}

    RNGenerator::RNGenerator(std::shared_ptr<Distribution> dist, const unsigned int &seed)
    : NumberGenerarator(std::move(dist), seed), generator_(seed_) {}

    double RNGenerator::generate(const int &step) {
        return (*dist_)(generator_);
    }

}
