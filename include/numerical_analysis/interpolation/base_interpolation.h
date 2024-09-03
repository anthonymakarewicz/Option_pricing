#ifndef BASE_INTERPOLATION_STRATEGY_H
#define BASE_INTERPOLATION_STRATEGY_H

#include <vector>

namespace OptionPricer {

    class Interpolation {
    public:
        virtual double interpolate(const std::vector<double>& xValues,
                                   const std::vector<double>& yValues,
                                   const double& xInterp) const = 0;
        virtual ~Interpolation();
    };

}

#endif //BASE_INTERPOLATION_STRATEGY_H
