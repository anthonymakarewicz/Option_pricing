#ifndef BASE_NUMBER_GENERATOR_H
#define BASE_NUMBER_GENERATOR_H

#include "random/distribution/base_distribution.h"

namespace OptionPricer {

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
