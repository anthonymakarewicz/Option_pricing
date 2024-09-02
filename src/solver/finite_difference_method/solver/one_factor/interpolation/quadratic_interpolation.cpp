#include "solver/finite_difference_method/solver/one_factor/interpolation/quadratic_interpolation.h"

namespace OptionPricer::FDM::OneFactor {

    double QuadraticInterpolation::interpolate(const std::vector<double> &prices,
                                               const std::vector<double> &grid,
                                               const double &S) const {
        if (S <= grid.front())
            return prices.front();
        if (S >= grid.back())
            return prices.back();

        // Perform binary search to locate the interval [x_k, x_{k+1}] that contains S
        const unsigned int k = findInterval(grid, S);

        // Ensure we have enough points for quadratic interpolation
        if (k == 0 || k == grid.size() - 2) {
            // If near the boundaries, fall back to linear interpolation
            return linearInterpolation(prices, grid, S, k);
        }

        // Perform quadratic interpolation using points k-1, k, k+1
        return quadraticInterpolation(prices, grid, S, k);
    }

    unsigned int QuadraticInterpolation::findInterval(const std::vector<double> &grid, const double &S) const {
        unsigned int low = 0;
        unsigned int high = grid.size() - 1;

        // Performs binary search assuming grid is strictly monotonous
        while (low <= high) {
            const unsigned int mid = low + (high - low) / 2;
            if (grid[mid] <= S && S <= grid[mid+1])
                return mid;
            if (grid[mid] < S)
                low = mid + 1;
            else
                high = mid - 1;
        }

        throw std::runtime_error("Interpolation error: Could not find appropriate interval.");
    }

    double QuadraticInterpolation::linearInterpolation(const std::vector<double> &prices,
                                                       const std::vector<double> &grid,
                                                       const double &S, const unsigned int &k) const {
            const double x1 = grid[k];
            const double x2 = grid[k+1];
            const double y1 = prices[k];
            const double y2 = prices[k+1];

            return y1 + (S-x1) * (y2-y1) / (x2-x1);
        }

    double QuadraticInterpolation::quadraticInterpolation(const std::vector<double> &prices,
                                                          const std::vector<double> &grid,
                                                          const double &S, const unsigned int &k) const {
        // Points used for interpolation
        const double x0 = grid[k-1], y0 = prices[k-1];
        const double x1 = grid[k], y1 = prices[k];
        const double x2 = grid[k+1], y2 = prices[k+1];

        // Quadratic interpolation formula
        const double L0 = ((S-x1) * (S-x2)) / ((x0-x1) * (x0-x2));
        const double L1 = ((S-x0) * (S-x2)) / ((x1-x0) * (x1-x2));
        const double L2 = ((S-x0) * (S-x1)) / ((x2-x0) * (x2-x1));

        return y0*L0 + y1*L1 + y2*L2;
    }

}
