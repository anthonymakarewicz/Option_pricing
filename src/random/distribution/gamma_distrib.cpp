#include "random/distribution/gamma_distrib.h"

namespace OptionPricer {

    GammaDistribution::GammaDistribution(const double &alpha, const double &beta)
    : alpha_(alpha), beta_(beta), gamma_dist_(alpha_, 1.0 / beta_) {
        if (alpha_ <= 0 || beta_ <= 0) {
            throw std::invalid_argument("alpha (shape) and beta (rate) parameters must be positive");
        }
    }

    GammaDistribution::~GammaDistribution() = default;

    double GammaDistribution::inv_cdf(const double &quantile) const {
        throw std::logic_error("Inverse CDF for Gamma Distribution not implemented yet.");
    }

    double GammaDistribution::operator()(std::mt19937 &gen) const {
        return gamma_dist_(gen);
    }

}
