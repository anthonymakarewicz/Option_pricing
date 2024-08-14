#include "random/distribution/standard_normal_distribution.h"

namespace OptionPricer {
    StandardNormalDistribution::StandardNormalDistribution()
    : normal_dist_(0.0, 1.0) {}

    StandardNormalDistribution::~StandardNormalDistribution() = default;

    double StandardNormalDistribution::inv_cdf(const double &quantile) const {
            /* This function implements the Beasley-Springer-Moro (BSM) algorithm
             * for approximating the inverse cumulative distribution function (CDF)
             * of the standard normal distribution, as described in Glasserman [2004].
             */

            if (quantile <= 0.0 || quantile >= 1.0) {
                throw std::invalid_argument("quantile must be between (0,1)");
            }

            const bool sup = quantile > 0.5;
            const double up = sup ? 1.0 - quantile : quantile;

            // Coefficients for the rational approximation of the central region
            static constexpr double a0 = 2.50662823884;
            static constexpr double a1 = -18.61500062529;
            static constexpr double a2 = 41.39119773534;
            static constexpr double a3 = -25.44106049637;

            static constexpr double b0 = -8.47351093090;
            static constexpr double b1 = 23.08336743743;
            static constexpr double b2 = -21.06224101826;
            static constexpr double b3 = 3.13082909833;

            // Coefficients for the polynomial approximation of the tail region
            static constexpr double c0 = 0.3374754822726147;
            static constexpr double c1 = 0.9761690190917186;
            static constexpr double c2 = 0.1607979714918209;
            static constexpr double c3 = 0.0276438810333863;
            static constexpr double c4 = 0.0038405729373609;
            static constexpr double c5 = 0.0003951896511919;
            static constexpr double c6 = 0.0000321767881768;
            static constexpr double c7 = 0.0000002888167364;
            static constexpr double c8 = 0.0000003960315187;

            double x = up - 0.5;
            double r;

            // Use rational approximation for quantiles in the central right region
            if (fabs(x) < 0.42) {
                r = x*x;
                r = x * (((a3*r + a2)*r + a1)*r + a0) / ((((b3*r + b2)*r + b1)*r + b0)*r + 1.0);
                return sup ? -r: r;
            }

            // Use Chebyshev polynomial approximation for quantiles in the right tail
            r = up;
            r = log(-log(r));
            r = c0 + r*(c1 + r*(c2 + r*(c3 + r*(c4 + r*(c5 + r*(c6 + r*(c7 + r*c8)))))));

            // Use symmetry property of the standard normal distribution
            return sup? r: -r;
        }

    double StandardNormalDistribution::operator()(std::mt19937 &gen) {
        return normal_dist_(gen);
    }

}
