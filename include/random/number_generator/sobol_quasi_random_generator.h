#ifndef SOBOL_QUASI_RANDOM_GENERATOR_H
#define SOBOL_QUASI_RANDOM_GENERATOR_H

#include <boost/random/sobol.hpp>
#include "random/number_generator/base_quasi_random_generator.h"

namespace OptionPricer {

    class SobolGenerator final: public QRNGenerator {
    public:
        explicit SobolGenerator(std::shared_ptr<Distribution> dist, const unsigned int& dim);
        SobolGenerator(std::shared_ptr<Distribution> dist, const unsigned int& seed, const unsigned int& dim);

        ~SobolGenerator() override;

        [[nodiscard]] double generate(const int& step) override;

    private:
        boost::random::sobol sobolQrng_;
    };

}

#endif //SOBOL_QUASI_RANDOM_GENERATOR_H
