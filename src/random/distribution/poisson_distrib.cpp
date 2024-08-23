#include "random/distribution/poisson_distrib.h"

namespace OptionPricer {

    PoissonDistribution::PoissonDistribution(const double& lambda)
    : lambda_(lambda), poisson_dist_(lambda_) {
        if (lambda_ <= 0.0) {
            throw std::invalid_argument("lambda must be positive");
        }
    }

    PoissonDistribution::~PoissonDistribution() = default;

    double PoissonDistribution::inv_cdf(const double &quantile) const {
        throw std::logic_error("Inverse CDF is not implemented yes for Poisson Distribution");
    }

    double PoissonDistribution::operator()(std::mt19937 &gen) const {
        return poisson_dist_(gen);
    }

}