#ifndef QUADRATIC_INTERPOLATION_H
#define QUADRATIC_INTERPOLATION_H

#include "numerical_analysis/interpolation/base_interpolation.h"

namespace OptionPricer {

    class QuadraticInterpolation final : public Interpolation {
    public:
        double interpolate(const std::vector<double>& xValues,
                           const std::vector<double>& yValues,
                           const double& xInterp) const override;

    private:
        // Time complexity O(log N)
        unsigned int findInterval(const std::vector<double>& xValues, const double &target) const;

        double linearInterpolation(const std::vector<double>& xValues,
                                   const std::vector<double>& yValues,
                                   const double &xInterp, const unsigned int &k) const;
        double quadraticInterpolation(const std::vector<double>& prices,
                                      const std::vector<double>& grid,
                                      const double &S, const unsigned int &k) const;
    };

}

#endif //QUADRATIC_INTERPOLATION_H
