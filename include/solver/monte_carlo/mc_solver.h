#ifndef MC_SOLVER_H
#define MC_SOLVER_H

#include "solver/base_solver.h"
#include "solver/monte_carlo/mc_base_strategy.h"

namespace OptionPricer {
    // Bridge between MCSolver and MCStrategy
    class MCSolver : public Solver {
    public:
        explicit MCSolver(const unsigned long& N = 100000)
            : N_(N), strategy_(nullptr) {}

        double solve() const override {
            if (!strategy_) {
                throw std::logic_error("Strategy is not set for MCSolver.");
            }
            return strategy_->calculate_price(N_);
        }

        void setN(const unsigned long& N) {
            N_ = N;
        }

        void setStrategy(std::unique_ptr<MCStrategy> strategy) {
            strategy_ = std::move(strategy);
        }

    private:
        unsigned long N_;
        std::unique_ptr<MCStrategy> strategy_;
    };
}

#endif //MC_SOLVER_H
