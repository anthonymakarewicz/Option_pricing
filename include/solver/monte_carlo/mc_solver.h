#ifndef MC_SOLVER_H
#define MC_SOLVER_H

#include "solver/base_solver.h"
#include "solver/monte_carlo/base_mc.h"

namespace OptionPricer {

    // Bridge between MCSolver and MCPricer
    class MCSolver final: public Solver {
    public:
        explicit MCSolver(const unsigned long& N = 100000);

        double solve() const override;
        void setN(const unsigned long& N);
        void setPricer(std::unique_ptr<MCPricer> pricer);

    private:
        unsigned long N_;
        std::unique_ptr<MCPricer> pricer_;
    };

}

#endif //MC_SOLVER_H

