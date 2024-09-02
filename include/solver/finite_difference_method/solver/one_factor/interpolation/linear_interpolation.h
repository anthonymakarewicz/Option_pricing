#ifndef LINEAR_INTERPOLATION_H
#define LINEAR_INTERPOLATION_H

#include "solver/finite_difference_method/solver/one_factor/interpolation/base_interpolation_strategy.h"

namespace OptionPricer::FDM::OneFactor {

    class LinearInterpolation : public InterpolationStrategy {
    public:
        double interpolate(const std::vector<double>& prices,
                           const std::vector<double>& grid,
                           const double& S) const override;
    };

}

#endif //LINEAR_INTERPOLATION_H
