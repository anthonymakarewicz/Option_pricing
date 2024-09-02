#include "solver/finite_difference_method/solver/one_factor/interpolation/linear_interpolation.h"

namespace OptionPricer::FDM::OneFactor {

    double LinearInterpolation::interpolate(const std::vector<double> &prices,
                                            const std::vector<double> &grid,
                                            const double& S) const {
        if (S <= grid.front())
            return prices.front();
        if (S >= grid.back())
            return prices.back();

        for (size_t i = 1; i < grid.size(); ++i) {
            if (S < grid[i]) {
                const double x1 = grid[i-1];
                const double x2 = grid[i];
                const double y1 = prices[i-1];
                const double y2 = prices[i];
                return y1 + (S-x1) * (y2-y1) / (x2-x1);
            }
        }
        throw std::runtime_error("Interpolation error: Price not within grid range.");
    }

}
