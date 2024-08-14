#ifndef STANDARD_NORMAL_DISTRIBUTION_H
#define STANDARD_NORMAL_DISTRIBUTION_H

#include <cmath>
#include "random/distribution/base_distribution.h"

namespace OptionPricer {

    class StandardNormalDistribution final: public Distribution {
    public:
        explicit StandardNormalDistribution();
        ~StandardNormalDistribution() override;

        [[nodiscard]] double inv_cdf(const double& quantile) const override;
        double operator()(std::mt19937& gen) override;

    private:
        std::normal_distribution<> normal_dist_;
    };

}

#endif //STANDARD_NORMAL_DISTRIBUTION_H
