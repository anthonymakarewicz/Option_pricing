#ifndef BASE_SOLVER_H
#define BASE_SOLVER_H

#include <memory>

#include "option/base_option.h"

namespace OptionPricer {
    class Solver {
    public:
        virtual ~Solver();
        virtual double solve(std::shared_ptr<Option> option) const = 0;
    };
}

#endif //BASE_SOLVER_H
