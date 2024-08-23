#include "solver/monte_carlo/mc_single_path.h"
#include "random/number_generator/base_quasi_random_generator.h"

namespace OptionPricer {

    SinglePathMCPricer::SinglePathMCPricer(std::shared_ptr<SinglePathOption> option,
                                           std::shared_ptr<IMarketData> marketData,
                                           std::shared_ptr<StockModel> stockModel)
        : MCPricer(std::move(marketData), std::move(stockModel)),
          option_(std::move(option)) {}

    double SinglePathMCPricer::calculatePrice(const unsigned long& N) const {
        double sumPayoff = 0.0;
        const double discountFactor = exp(-marketData_->getR() * option_->getT());

        for (int i = 0; i < N; ++i) {
            double S_T = stockModel_->simulatePriceAtMaturity(option_->getT());
            sumPayoff += option_->payoff(S_T);
        }

        return (sumPayoff / static_cast<double>(N)) * discountFactor;
    }

}




