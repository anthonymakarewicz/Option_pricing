#ifndef STANDARD_NORMAL_DISTRIBUTION_H
#define STANDARD_NORMAL_DISTRIBUTION_H

#include <cmath>
#include "random/distribution/normal_distrib.h"

namespace OptionPricer {

    class StandardNormalDistribution final: public NormalDistribution {
    public:
        explicit StandardNormalDistribution();
        ~StandardNormalDistribution() override;

        [[nodiscard]] double inv_cdf(const double& quantile) const override;
    };

}

#endif //STANDARD_NORMAL_DISTRIBUTION_H
