#include "solver/monte_carlo/builder/base_mc_builder.h"
#include "market_data/market_data.h"

namespace OptionPricer {

    MCBuilder::MCBuilder()
    : marketData_(MarketData::getInstance()) {}

    MCBuilder::~MCBuilder() = default;

    MCBuilder & MCBuilder::setMarketData(std::shared_ptr<IMarketData> marketData) {
        marketData_ = std::move(marketData); // For injecting Mock MarketData in Unit Test
        return *this;
    }

    MCBuilder & MCBuilder::setStockPriceModel(std::shared_ptr<StockModel> stockModel) {
        stockModel_ = std::move(stockModel);
        return *this;
    }
}
