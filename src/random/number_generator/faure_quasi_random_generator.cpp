#include "random/number_generator/faure_quasi_random_generator.h"

namespace OptionPricer {

    FaureGenerator::FaureGenerator(const unsigned int &dim)
    : QuasiRandomNumberGenerator(dim), faureQrng_(dim_) {
        faureQrng_.seed(seed_);
        faureQrng_.generate(point_.begin(), point_.end()); // Initialize the point
    }

    FaureGenerator::FaureGenerator(const unsigned int &dim,
                                   const unsigned int &seed)
    : QuasiRandomNumberGenerator(dim, seed), faureQrng_(dim_) {
        faureQrng_.seed(seed_);
        faureQrng_.generate(point_.begin(), point_.end());
    }

    FaureGenerator::~FaureGenerator() = default;

    double FaureGenerator::operator()(Distribution& dist) const {
        if (step_ >= dim_) {
            faureQrng_.generate(point_.begin(), point_.end());
            step_ = 0; // Reset step
        }

        // Normalize and transform using the inverse CDF
        const double uniform_value = point_[step_] / static_cast<double>(boost::random::faure::max());
        ++step_;
        return dist.inv_cdf(uniform_value);
    }

}
