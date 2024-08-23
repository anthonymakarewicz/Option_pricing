#include "random/distribution/exponential_distr.h"

namespace OptionPricer {

    ExponentialDistribution::ExponentialDistribution(const double &lambda)
    : lambda_(lambda), exponential_dist_(lambda_) {
        if (lambda_ <= 0)
            throw std::invalid_argument("lambda must be positive");
    }

    ExponentialDistribution::~ExponentialDistribution() = default;

    double ExponentialDistribution::inv_cdf(const double &quantile) const {
        throw std::logic_error("Inverse CDF for Normal Distribution nor implemented yet.");
    }

    double ExponentialDistribution::operator()(std::mt19937 &gen) const {
        return exponential_dist_(gen);
    }

}