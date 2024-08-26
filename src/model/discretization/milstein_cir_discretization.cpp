#include "model/discretization/milstein_cir_discretization.h"

namespace OptionPricer {
    void CIRMilsteinDiscretization::update(double &V, const double &dt,
                                           const double &kappa, const double &theta,
                                           const double &sigma_v, const double &z) const {
        // Apply Explicit Euler first
        CIRExplicitEulerDiscretization::update(V, dt, kappa, theta, sigma_v, z);

        // Add the Milstein correction term
        V += 0.25 * sigma_v*sigma_v * dt * (z*z - 1);
    }
}