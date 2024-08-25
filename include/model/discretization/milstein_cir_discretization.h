#ifndef MILSTEIN_CIR_DISCRETIZATION_H
#define MILSTEIN_CIR_DISCRETIZATION_H

#include "model/discretization/explicit_euler_cir_discretization.h"

namespace OptionPricer {

    class CIRMilsteinDiscretization : public CIRExplicitEulerDiscretization {
    public:
        void update(double &V, const double &dt, const double &kappa, const double &theta, const double &sigma_v,
            const double &z) const override;
    };

}

#endif //MILSTEIN_CIR_DISCRETIZATION_H
