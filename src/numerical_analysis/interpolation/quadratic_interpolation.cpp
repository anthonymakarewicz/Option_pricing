#include "numerical_analysis/interpolation/quadratic_interpolation.h"

namespace OptionPricer {

    double QuadraticInterpolation::interpolate(const std::vector<double> &xValues,
                                               const std::vector<double> &yValues,
                                               const double &xInterp) const {
        if (xInterp <= xValues.front())
            return yValues.front();
        if (xInterp >= xValues.back())
            return yValues.back();

        // Perform binary search to locate the interval [x_k, x_{k+1}] that contains S
        const unsigned int k = findInterval(xValues, xInterp);

        // Ensure we have enough points for quadratic interpolation
        if (k == 0 || k == xValues.size() - 2) {
            // If near the boundaries, fall back to linear interpolation
            return linearInterpolation(xValues, yValues, xInterp, k);
        }

        // Perform quadratic interpolation using points k-1, k, k+1
        return quadraticInterpolation(yValues, xValues, xInterp, k);
    }

    unsigned int QuadraticInterpolation::findInterval(const std::vector<double> &xValues, const double &target) const {
        unsigned int low = 0;
        unsigned int high = xValues.size() - 1;

        // Performs binary search assuming grid is strictly monotonous
        while (low <= high) {
            const unsigned int mid = low + (high - low) / 2;
            if (xValues[mid] <= target && target <= xValues[mid+1])
                return mid;
            if (xValues[mid] < target)
                low = mid + 1;
            else
                high = mid - 1;
        }

        throw std::runtime_error("Interpolation error: Could not find appropriate interval.");
    }

    double QuadraticInterpolation::linearInterpolation(const std::vector<double> &xValues,
                                                       const std::vector<double> &yValues,
                                                       const double &xInterp, const unsigned int &k) const {
            const double x1 = xValues[k];
            const double x2 = xValues[k+1];
            const double y1 = yValues[k];
            const double y2 = yValues[k+1];

            return y1 + (xInterp-x1) * (y2-y1) / (x2-x1);
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
