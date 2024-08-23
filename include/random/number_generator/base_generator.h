#ifndef BASE_NUMBER_GENERATOR_H
#define BASE_NUMBER_GENERATOR_H

#include "random/distribution/base_distribution.h"

namespace OptionPricer {

    class NumberGenerator {
    public:
        explicit NumberGenerator(const unsigned int &dim);
        explicit NumberGenerator(const unsigned int &dim, const unsigned int& seed);

        virtual ~NumberGenerator();

        virtual double operator()(Distribution &dist) const = 0;
        unsigned int getDim() const;

    protected:
        void validateDim() const;
        unsigned int dim_;
        unsigned int seed_;
    };

}

#endif //BASE_NUMBER_GENERATOR_H