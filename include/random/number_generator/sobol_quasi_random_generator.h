#ifndef SOBOL_QUASI_RANDOM_GENERATOR_H
#define SOBOL_QUASI_RANDOM_GENERATOR_H

#include <boost/random/sobol.hpp>
#include "random/number_generator/base_quasi_random_generator.h"

namespace OptionPricer {

    class SobolGenerator final: public QuasiRandomNumberGenerator {
    public:
        explicit SobolGenerator(const unsigned int& dim);
        SobolGenerator(const unsigned int& dim, const unsigned int& seed);

        ~SobolGenerator() override;

        double operator()(Distribution& dist) const override;

    private:
        mutable boost::random::sobol sobolQrng_;
    };

}

#endif //SOBOL_QUASI_RANDOM_GENERATOR_H
