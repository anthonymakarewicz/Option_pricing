#ifndef CONTINUOUS_UNIFORM_DISTRIB_H
#define CONTINUOUS_UNIFORM_DISTRIB_H

#include "random/distribution/base_distribution.h"

namespace OptionPricer {

    class ContinuousUniformDistribution : public Distribution {
    public:
        explicit ContinuousUniformDistribution(const double& a = 0.0, const double& b = 1.0);
        ~ContinuousUniformDistribution() override;

        [[nodiscard]] double inv_cdf(const double& quantile) const override;
        double operator()(std::mt19937& gen) const override;

    protected:
        double a_; // Lower bound
        double b_; // Upper bound
        mutable std::uniform_real_distribution<> uniform_dist_;
    };

}

#endif //CONTINUOUS_UNIFORM_DISTRIB_H
