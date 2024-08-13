#include "solver/monte_carlo/base_mc_path_dependent.h"

namespace OptionPricer {

    PathDependentMCPricer::PathDependentMCPricer(std::shared_ptr<IMarketData> marketData,
                                                 std::shared_ptr<StockPriceModel> stockModel,
                                                 std::shared_ptr<NumberGenerarator> generator,
                                                 const unsigned int &steps)
    : MCPricer(std::move(marketData), std::move(stockModel), std::move(generator)),
              steps_(steps) {
        if (const auto generatorQR = std::dynamic_pointer_cast<QRNGenerator>(generator_)) {
            if (generatorQR->getDim() != steps_) {
                steps_ = static_cast<int>(generatorQR->getDim());
                std::cerr << "For PathDependent options, the steps parameter ";
                std::cerr << "must be equal to the dim of derived QRNGenerator." << "\n";
                std::cerr << "steps is thus set to " << generatorQR->getDim() << "\n";
            }
        }
    }

}
