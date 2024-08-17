#ifndef BASE_NUMBER_GENERATOR_H
#define BASE_NUMBER_GENERATOR_H

#include "random/distribution/base_distribution.h"

namespace OptionPricer {

    // MAYB PUTTING THE CREATION INSIDE A STOCKMODEL FACTORY THAT WOULD REQUIRE A THE DIM PARAMETER
    // TO BE PASSED TO BOTH THE QUASI RANDOM NUMBER GENERATOR AS WELL AS THE STOCKPRICEMODEL CLASS
    class NumberGenerator {
    public:
        explicit NumberGenerator(std::shared_ptr<Distribution> dist);
        explicit NumberGenerator(std::shared_ptr<Distribution> dist, const unsigned int& seed);

        virtual ~NumberGenerator();

        virtual double generate(const int& step) = 0;

    protected:
        std::shared_ptr<Distribution> dist_;
        unsigned int seed_;
    };

}

#endif //BASE_NUMBER_GENERATOR_H