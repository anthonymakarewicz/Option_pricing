#include "random/distribution/continuous_uniform_distrib.h"

namespace OptionPricer {
    ContinuousUniformDistribution::ContinuousUniformDistribution(const double &a, const double &b)
    : a_(a), b_(b) {
        if (a_ >= b_)
            throw std::invalid_argument("a must lower than b");
    }

    ContinuousUniformDistribution::~ContinuousUniformDistribution() = default;

    double ContinuousUniformDistribution::inv_cdf(const double &quantile) const {
        throw std::logic_error("Inverse CDF for Uniform Distribution not implemented yet.");
    }

    double ContinuousUniformDistribution::operator()(std::mt19937 &gen) const {
        return uniform_dist_(gen);
    }

}