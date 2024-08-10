#include "solver/monte_carlo/mc_base_strategy.h"

/*
namespace OptionPricer {
    MCStrategy::~MCStrategy() = default;

    double MCStrategy::calculate_price(std::shared_ptr<Option> option, int num_simulations) {
        initialize(option);
        double sum_payoff = 0.0;

        for (int i = 0; i < num_simulations; ++i) {
            double S_t = simulate_path(option);
            sum_payoff += calculate_payoff(S_t, option);
        }

        return finalize_price(sum_payoff, option, num_simulations);
    }

    double MCStrategy::finalize_price(double sum_payoff, std::shared_ptr<Option> option, int num_simulations) const {
        return (sum_payoff / num_simulations) * exp(-option->getID() * option->T_);
    }
}

*/