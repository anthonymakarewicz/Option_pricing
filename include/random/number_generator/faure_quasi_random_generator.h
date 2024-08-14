#ifndef FAURE_QUASI_RANDOM_GENERATOR_H
#define FAURE_QUASI_RANDOM_GENERATOR_H

#include <boost/random/faure.hpp>
#include "random/number_generator/base_quasi_random_generator.h"

namespace OptionPricer {

    class FaureGenerator final: public QRNGenerator {
    public:
        explicit FaureGenerator(std::shared_ptr<Distribution> dist, const unsigned int& dim);
        FaureGenerator(std::shared_ptr<Distribution> dist, const unsigned int& seed, const unsigned int& dim);

        ~FaureGenerator() override;

        [[nodiscard]] double generate(const int& step) override;

    private:
        boost::random::faure faureQrng_;
    };

}

#endif //FAURE_QUASI_RANDOM_GENERATOR_H
