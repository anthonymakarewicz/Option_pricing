#ifndef BASE_CIR_DISCRETIZATION_H
#define BASE_CIR_DISCRETIZATION_H

#include <algorithm>

namespace OptionPricer {

    class CIRDiscretization {
    public:
        virtual ~CIRDiscretization();
        virtual double apply(const double &v, const double &dt,
                             const double &kappa, const double &theta,
                             const double &sigma_v, const double &z) const = 0;
    };

}

#endif //BASE_CIR_DISCRETIZATION_H
