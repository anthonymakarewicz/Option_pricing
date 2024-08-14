#include "random/number_generator/base_quasi_random_generator.h"

namespace OptionPricer {

    QRNGenerator::QRNGenerator(std::shared_ptr<Distribution> dist, const unsigned int &dim)
    : NumberGenerarator(std::move(dist)), dim_(dim), point_(dim_) {
        validateDim();
    }

    QRNGenerator::QRNGenerator(std::shared_ptr<Distribution> dist, const unsigned int &seed, const unsigned int &dim)
    : NumberGenerarator(std::move(dist), seed), dim_(dim), point_(dim_) {
        validateDim();
    }

    QRNGenerator::~QRNGenerator() = default;

    unsigned int QRNGenerator::getDim() const {
        return dim_;
    }

    void QRNGenerator::validateDim() const {
        if (dim_ < 0) {
            throw std::invalid_argument("dim must be a positive integer");
        }
    }


}
