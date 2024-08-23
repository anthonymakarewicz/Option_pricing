#ifndef GAMMA_DISTRIB_H
#define GAMMA_DISTRIB_H

#include "random/distribution/base_distribution.h"

namespace OptionPricer {

    class GammaDistribution : public Distribution {
    public:
        GammaDistribution(const double& alpha, const double& beta);
        ~GammaDistribution() override;

        [[nodiscard]] double inv_cdf(const double& quantile) const override;
        double operator()(std::mt19937& gen) const override;

    protected:
        double alpha_; // Shape parameter
        double beta_;  // Rate parameter
        mutable std::gamma_distribution<> gamma_dist_;
    };

}

#endif //GAMMA_DISTRIB_H
