#ifndef BASE_MC_BUILDER_PATH_DEPENDENT_H
#define BASE_MC_BUILDER_PATH_DEPENDENT_H

#include "solver/monte_carlo/builder/base_mc_builder.h"

namespace OptionPricer {

    class PathDependentMCBuilder : public MCBuilder {
    public:
        PathDependentMCBuilder();
        ~PathDependentMCBuilder() override;

        PathDependentMCBuilder& setSteps(unsigned int steps);

    protected:
        unsigned int steps_;
    };

}

#endif //BASE_MC_BUILDER_PATH_DEPENDENT_H
