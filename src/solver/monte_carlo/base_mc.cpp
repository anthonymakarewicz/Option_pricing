#include "solver/monte_carlo/base_mc.h"

namespace OptionPricer {

    MCPricer::MCPricer(std::shared_ptr<IMarketData> marketData, std::shared_ptr<StockModel> stockModel)
    : marketData_(std::move(marketData)), stockModel_(std::move(stockModel)) {}

    MCPricer::~MCPricer() = default;

}
