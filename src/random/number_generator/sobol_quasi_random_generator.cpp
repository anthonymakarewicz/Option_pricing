#include "random/number_generator/sobol_quasi_random_generator.h"

namespace OptionPricer {

    SobolGenerator::SobolGenerator(std::shared_ptr<Distribution> dist, const unsigned int &dim)
    : QRNGenerator(std::move(dist), dim), sobolQrng_(dim_) {
        sobolQrng_.seed(seed_);
    }

    SobolGenerator::SobolGenerator(std::shared_ptr<Distribution> dist,
                                   const unsigned int &seed,
                                   const unsigned int &dim)
    : QRNGenerator(std::move(dist),seed, dim), sobolQrng_(dim_) {
        sobolQrng_.seed(seed_);
    }

    SobolGenerator::~SobolGenerator() = default;

    double SobolGenerator::generate(const int &step) {
        if (step == 0) {
            // Generate Sobol sequence point
            sobolQrng_.generate(point_.begin(), point_.end());
        }

        // Normalize and transform using Moro's inversion
        const double uniformValue = point_[step] / static_cast<double>(boost::random::sobol::max());
        return dist_->inv_cdf(uniformValue);
    }

}
