#include "solver/monte_carlo/mc_single_path.h"
#include "random/number_generator/base_quasi_random_generator.h"

namespace OptionPricer {

    SinglePathMCPricer::SinglePathMCPricer(std::shared_ptr<SinglePathOption> option,
                                           std::shared_ptr<IMarketData> marketData,
                                           std::shared_ptr<StockModel> stockModel,
                                           std::shared_ptr<NumberGenerator> generator)
        : MCPricer(std::move(marketData), std::move(stockModel), std::move(generator)),
          option_(std::move(option)) {
        if (const auto generatorQR = std::dynamic_pointer_cast<QuasiRandomNumberGenerator>(generator_)) {
            if (generatorQR->getDim() != 1) {
                throw std::invalid_argument("For SinglePath options, the dim parameter of QuasiRandomNumberGenerator must be 1");
            }
        }
    }

    double SinglePathMCPricer::calculatePrice(const unsigned long& N) const {
        double sumPayoff = 0.0;

        for (int i = 0; i < N; ++i) {
            const double z = generator_->generate(0);
            double S_T = stockModel_->simulatePriceAtMaturity(option_->getT(), z);
            sumPayoff += option_->payoff(S_T);
        }

        return (sumPayoff / static_cast<double>(N)) * exp(-marketData_->getR() * option_->getT());
    }

}




