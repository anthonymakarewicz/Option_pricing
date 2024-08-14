#ifndef BASE_QUASI_RANDOM_GENERATOR_H
#define BASE_QUASI_RANDOM_GENERATOR_H

#include "random/number_generator/base_generator.h"

namespace OptionPricer {

    class QRNGenerator : public NumberGenerarator {
    public:
        explicit QRNGenerator(std::shared_ptr<Distribution> dist, const unsigned int& dim);
        QRNGenerator(std::shared_ptr<Distribution> dist, const unsigned int& seed, const unsigned int& dim);

        ~QRNGenerator() override;

        unsigned int getDim() const;

    protected:
        void validateDim() const;

        unsigned int dim_;
        std::vector<double> point_; // Maybe use array
    };

}

#endif //BASE_QUASI_RANDOM_GENERATOR_H
