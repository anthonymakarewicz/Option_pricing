#ifndef MC_SOLVER_H
#define MC_SOLVER_H

#include <memory>
#include "market_data/interface_market_data.h"
#include "stock_price_model.h"
#include "number_generator.h"
#include "option/base_option.h"

namespace OptionPricer {
    class MonteCarloSolver : public MarketDataObserver {
    public:
        MonteCarloSolver(std::shared_ptr<Option> option,
                         std::shared_ptr<StockPriceModel> stockModel,
                         std::shared_ptr<NumberGenerator> generator,
                         int num_simulations)
            : option_(std::move(option)),
              stockModel_(std::move(stockModel)),
              generator_(std::move(generator)),
              num_simulations_(num_simulations) {}

        void update() override {
            double price = calculate_price();
            option_->setPrice(price);
            std::cout << "Updated Option Price: " << price << "\n";
        }

    private:
        double calculate_price() const {
            double sum_payoff = 0.0;
            for (int i = 0; i < num_simulations_; ++i) {
                double S_t = simulate_path();
                sum_payoff += calculate_payoff(S_t);
            }
            return finalize_price(sum_payoff);
        }

        double simulate_path() const {
            // Implement your path simulation logic here
            return 0.0; // Placeholder
        }

        double calculate_payoff(double S_t) const {
            return option_->payoff(S_t);
        }

        double finalize_price(double sum_payoff) const {
            return (sum_payoff / num_simulations_) * exp(-option_->getT() * option_->marketData_->getR());
        }

        std::shared_ptr<Option> option_;
        std::shared_ptr<StockPriceModel> stockModel_;
        std::shared_ptr<NumberGenerator> generator_;
        int num_simulations_;
    };
}

#endif //MC_SOLVER_H
