#ifndef POISSON_DISTRIB_H
#define POISSON_DISTRIB_H

#include "random/distribution/base_distribution.h"

namespace OptionPricer {

    class PoissonDistribution final: public Distribution {
    public:
        explicit PoissonDistribution(const double& lambda);
        ~PoissonDistribution() override;

        [[nodiscard]] double inv_cdf(const double& quantile) const override;
        double operator()(std::mt19937& gen) const override;

    private:
        double lambda_;
        mutable std::poisson_distribution<> poisson_dist_;
    };

}

#endif //POISSON_DISTRIB_H