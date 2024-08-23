#include "random/distribution/normal_distrib.h"

namespace OptionPricer {

    NormalDistribution::NormalDistribution(const double &mu, const double &sigma)
    : mu_(mu), sigma_(sigma), normal_dist_(mu_, sigma_) {
        if (sigma_ <= 0)
            throw std::invalid_argument("sigma must be positive");
    }

    NormalDistribution::~NormalDistribution() = default;

    double NormalDistribution::inv_cdf(const double &quantile) const {
        throw std::logic_error("Inverse CDF for Normal Distribution nor implemented yet.");
    }

    double NormalDistribution::operator()(std::mt19937 &gen) const {
        return normal_dist_(gen);
    }

}
