#ifndef EXPLICIT_EULER_CIR_DISCRETIZATION_H
#define EXPLICIT_EULER_CIR_DISCRETIZATION_H

#include "model/discretization/base_cir_discretization.h"

namespace OptionPricer {

    class CIRExplicitEulerDiscretization : public CIRDiscretization {
    public:
        double apply(const double &v, const double &dt,
                     const double &kappa, const double &theta,
                     const double &sigma_v, const double &z) const override;
    };

}

#endif //EXPLICIT_EULER_CIR_DISCRETIZATION_H
