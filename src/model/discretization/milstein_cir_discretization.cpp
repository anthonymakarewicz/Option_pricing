#include "model/discretization/milstein_cir_discretization.h"

namespace OptionPricer {
    double CIRMilsteinDiscretization::apply(const double &v, const double &dt,
                                            const double &kappa, const double &theta,
                                            const double &sigma_v, const double &z) const {
        // Apply Explicit Euler first
        double vNew = CIRExplicitEulerDiscretization::apply(v, dt, kappa, theta, sigma_v, z);

        // Add the Milstein correction term
        vNew += 0.25 * sigma_v*sigma_v * dt * (z*z - 1);

        return vNew;
    }
}
