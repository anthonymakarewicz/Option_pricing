#ifndef BASE_INTERPOLATION_STRATEGY_H
#define BASE_INTERPOLATION_STRATEGY_H

#include <vector>

namespace OptionPricer::FDM::OneFactor {

    class InterpolationStrategy {
    public:
        virtual double interpolate(const std::vector<double>& prices,
                                   const std::vector<double>& grid,
                                   const double& S) const = 0;
        virtual ~InterpolationStrategy();
    };

}

#endif //BASE_INTERPOLATION_STRATEGY_H
