#include "solver/monte_carlo/base_mc.h"

namespace OptionPricer {

    MCPricer::MCPricer(std::shared_ptr<IMarketData> marketData,
                       std::shared_ptr<StockModel> stockModel,
                       std::shared_ptr<NumberGenerator> generator)
    : marketData_(std::move(marketData)), stockModel_(std::move(stockModel)),
    generator_(std::move(generator)) {}

    MCPricer::~MCPricer() = default;

}
