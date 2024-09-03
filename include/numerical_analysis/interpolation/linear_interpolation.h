#ifndef LINEAR_INTERPOLATION_H
#define LINEAR_INTERPOLATION_H

#include "numerical_analysis/interpolation/base_interpolation.h"

namespace OptionPricer {

    class LinearInterpolation : public Interpolation {
    public:
        double interpolate(const std::vector<double>& xValues,
                           const std::vector<double>& yValues,
                           const double& xInterp) const override;
    };

}

#endif //LINEAR_INTERPOLATION_H
