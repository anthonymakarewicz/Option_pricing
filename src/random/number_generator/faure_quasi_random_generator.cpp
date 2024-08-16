#include "random/number_generator/faure_quasi_random_generator.h"

namespace OptionPricer {

    FaureGenerator::FaureGenerator(std::shared_ptr<Distribution> dist, const unsigned int &dim)
    : QuasiRandomNumberGenerator(std::move(dist), dim), faureQrng_(dim_) {
        faureQrng_.seed(seed_);
    }

    FaureGenerator::FaureGenerator(std::shared_ptr<Distribution> dist,
                                   const unsigned int &seed,
                                   const unsigned int &dim)
    : QuasiRandomNumberGenerator(std::move(dist), seed, dim), faureQrng_(dim_) {
        faureQrng_.seed(seed_);
    }

    FaureGenerator::~FaureGenerator() = default;

    double FaureGenerator::generate(const int &step) {
        if (step == 0) {
            // Generate Sobol sequence point
            faureQrng_.generate(point_.begin(), point_.end());
        }

        // Normalize and transform using the inverse CDF
        const double uniform_value = point_[step] / static_cast<double>(boost::random::faure::max());
        return dist_->inv_cdf(uniform_value);
    }

}
