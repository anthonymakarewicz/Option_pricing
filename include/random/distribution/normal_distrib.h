#ifndef NORMAL_DISTRIBUTION_H
#define NORMAL_DISTRIBUTION_H

#include <cmath>
#include "random/distribution/base_distribution.h"

namespace OptionPricer {

    class NormalDistribution : public Distribution {
    public:
        explicit NormalDistribution(const double& mu, const double& sigma);
        ~NormalDistribution() override;

        [[nodiscard]] double inv_cdf(const double& quantile) const override;
        double operator()(std::mt19937& gen) const override;

    protected:
        double mu_;
        double sigma_;
        mutable std::normal_distribution<> normal_dist_;
    };

}

#endif //NORMAL_DISTRIBUTION_H
