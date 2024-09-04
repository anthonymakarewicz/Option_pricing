#include "numerical_analysis/interpolation/linear_interpolation.h"

namespace OptionPricer {

    double LinearInterpolation::interpolate(const std::vector<double> &xValues,
                                            const std::vector<double> &yValues,
                                            const double& xInterp) const {
        if (xInterp <= xValues.front())
            return yValues.front();
        if (xInterp >= xValues.back())
            return yValues.back();

        for (size_t i = 1; i < xValues.size(); ++i) {
            if (xInterp < xValues[i]) {
                const double x1 = xValues[i-1];
                const double x2 = xValues[i];
                const double y1 = yValues[i-1];
                const double y2 = yValues[i];
                return y1 + (xInterp-x1) * (y2-y1) / (x2-x1);
            }
        }
        throw std::runtime_error("Interpolation error: Price not within grid range.");
    }

}
