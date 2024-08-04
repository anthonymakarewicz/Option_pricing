#ifndef MC_BASE_STRATEGY_H
#define MC_BASE_STRATEGY_H

#include "option/base_option.h"

namespace OptionPricer {
    class MCStrategy {
    public:
        virtual ~MCStrategy();
        double calculate_price(std::shared_ptr<Option> option, int num_simulations);

    protected:
        virtual void initialize(std::shared_ptr<Option> option) const = 0;
        virtual double simulate_path(std::shared_ptr<Option> option) const = 0;
        double calculate_payoff(const double& S_t, std::shared_ptr<Option> option) const;

        double finalize_price(double sum_payoff, std::shared_ptr<Option> option, int num_simulations) const;

    };
}



#endif //MC_BASE_STRATEGY_H
