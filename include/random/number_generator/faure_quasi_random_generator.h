#ifndef FAURE_QUASI_RANDOM_GENERATOR_H
#define FAURE_QUASI_RANDOM_GENERATOR_H

#include <boost/random/faure.hpp>
#include "random/number_generator/base_quasi_random_generator.h"

namespace OptionPricer {

    class FaureGenerator final: public QuasiRandomNumberGenerator {
    public:
        explicit FaureGenerator(const unsigned int& dim);
        FaureGenerator(const unsigned int& seed, const unsigned int& dim);

        ~FaureGenerator() override;

        double operator()(Distribution& dist) const override;

    private:
        mutable boost::random::faure faureQrng_;
    };

}

#endif //FAURE_QUASI_RANDOM_GENERATOR_H
