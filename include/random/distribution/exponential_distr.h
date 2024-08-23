#ifndef EXPONENTIAL_DISTR_H
#define EXPONENTIAL_DISTR_H

#include "random/distribution/base_distribution.h"

namespace OptionPricer {

    class ExponentialDistribution : public Distribution {
    public:
        explicit ExponentialDistribution(const double& lambda);
        ~ExponentialDistribution() override;

        [[nodiscard]] double inv_cdf(const double& quantile) const override;
        double operator()(std::mt19937& gen) const override;

    protected:
        double lambda_; // Intensity rate
        mutable std::exponential_distribution<> exponential_dist_;
    };

}

#endif //EXPONENTIAL_DISTR_H