#ifndef BASE_SOLVER_H
#define BASE_SOLVER_H

#include <memory>

namespace OptionPricer {

    class Solver {
    public:
        virtual ~Solver();
        [[nodiscard]] virtual double solve() const = 0;
    };

}

#endif //BASE_SOLVER_H
