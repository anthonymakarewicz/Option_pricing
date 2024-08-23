#include "model/discretization/explicit_euler_cir_discretization.h"

namespace OptionPricer {

    double CIRExplicitEulerDiscretization::apply(const double &v, const double &dt,
                                                 const double &kappa, const double &theta,
                                                 const double &sigma_v, const double &z) const {
        // Apply Full Truncation
        const double vMax = std::max(v, 0.0);
        return v + kappa * (theta-vMax) * dt + sigma_v * sqrt(vMax*dt) * z;
    }

}
