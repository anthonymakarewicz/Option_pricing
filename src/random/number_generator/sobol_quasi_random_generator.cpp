#include "random/number_generator/sobol_quasi_random_generator.h"

namespace OptionPricer {

    SobolGenerator::SobolGenerator(const unsigned int &dim)
    : QuasiRandomNumberGenerator(dim), sobolQrng_(dim_) {
        sobolQrng_.seed(seed_);
        sobolQrng_.generate(point_.begin(), point_.end()); // Initialize the point
    }

    SobolGenerator::SobolGenerator(const unsigned int &dim,
                                   const unsigned int &seed)
    : QuasiRandomNumberGenerator(dim, seed), sobolQrng_(dim_) {
        sobolQrng_.seed(seed_);
        sobolQrng_.generate(point_.begin(), point_.end());
    }

    SobolGenerator::~SobolGenerator() = default;

    double SobolGenerator::operator()(Distribution& dist) const {
        if (step_ >= dim_) {
            sobolQrng_.generate(point_.begin(), point_.end());
            step_ = 0; // Reset step
        }

        // Normalize and transform using Moro's inversion
        const double uniformValue = point_[step_] / static_cast<double>(boost::random::sobol::max());
        ++step_;  // Increment step after use
        return dist.inv_cdf(uniformValue);
    }

}
