#include "solver/monte_carlo/builder/base_mc_builder_path_dependent.h"

namespace OptionPricer {

    PathDependentMCBuilder::PathDependentMCBuilder()
    : MCBuilder(), steps_(52) {}

    PathDependentMCBuilder::~PathDependentMCBuilder() = default;

    PathDependentMCBuilder & PathDependentMCBuilder::setSteps(unsigned int steps) {
        steps_ = steps;
        return *this;
    }

}

