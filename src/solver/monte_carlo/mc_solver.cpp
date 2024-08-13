#include "solver/monte_carlo/mc_solver.h"

namespace OptionPricer {

    MCSolver::MCSolver(const unsigned long& N)
        : N_(N), pricer_(nullptr) {}

    double MCSolver::solve() const {
        if (!pricer_) {
            throw std::logic_error("Pricer is not set for MonteCarloSolver.");
        }
        return pricer_->calculate_price(N_);
    }

    void MCSolver::setN(const unsigned long& N) {
        N_ = N;
    }

    void MCSolver::setPricer(std::unique_ptr<MCPricer> pricer) {
        pricer_ = std::move(pricer);
    }

}