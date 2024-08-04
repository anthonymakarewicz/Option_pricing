#ifndef MC_SOLVER_H
#define MC_SOLVER_H

#include "solver/base_solver.h"
#include "solver/monte_carlo/mc_base_strategy.h"

namespace OptionPricer {
    class MCSolver : public Solver {
    public:
        MCSolver(int num_simulations, std::unique_ptr<MCStrategy> strategy)
            : num_simulations_(num_simulations), strategy_(std::move(strategy)) {}

        double solve(std::shared_ptr<Option> option) const override {
            return strategy_->calculate_price(option, num_simulations_);
        }

    private:
        int num_simulations_;
        std::unique_ptr<MCStrategy> strategy_;
    };
}

#endif //MC_SOLVER_H
