#include "model/discretization/explicit_euler_cir_discretization.h"

namespace OptionPricer {

    void CIRExplicitEulerDiscretization::update(double &V, const double &dt,
                                                  const double &kappa, const double &theta,
                                                  const double &sigma_v, const double &z) const {
        // Apply Full Truncation
        const double vMax = std::max(V, 0.0);
        V +=  kappa * (theta-vMax) * dt + sigma_v * sqrt(vMax*dt) * z;
    }

}
