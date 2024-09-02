#ifndef QUADRATIC_INTERPOLATION_H
#define QUADRATIC_INTERPOLATION_H

#include "solver/finite_difference_method/solver/one_factor/interpolation/base_interpolation_strategy.h"

namespace OptionPricer::FDM::OneFactor {

    class QuadraticInterpolation final : public InterpolationStrategy {
    public:
        double interpolate(const std::vector<double>& prices,
                           const std::vector<double>& grid,
                           const double& S) const override;

    private:
        // Time complexity O(log N)
        unsigned int findInterval(const std::vector<double>& grid, const double &S) const;

        double linearInterpolation(const std::vector<double>& prices,
                                   const std::vector<double>& grid,
                                   const double &S, const unsigned int &k) const;
        double quadraticInterpolation(const std::vector<double>& prices,
                                      const std::vector<double>& grid,
                                      const double &S, const unsigned int &k) const;
    };

}

#endif //QUADRATIC_INTERPOLATION_H
