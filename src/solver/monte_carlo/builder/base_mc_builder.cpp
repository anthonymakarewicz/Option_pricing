#include "solver/monte_carlo/builder/base_mc_builder.h"
#include "market_data/market_data.h"
#include "random/distribution/standard_normal_distribution.h"
#include "random/number_generator/random_generator.h"

namespace OptionPricer {

    MCBuilder::MCBuilder()
    : marketData_(MarketData::getInstance()), // Default to MarketData Singleton
      generator_(std::make_shared<RNGenerator>(std::make_shared<StandardNormalDistribution>())) {}

    MCBuilder::~MCBuilder() = default;

    MCBuilder & MCBuilder::setMarketData(std::shared_ptr<IMarketData> marketData) {
        marketData_ = std::move(marketData); // For injecting Mock MarketData in Unit Test
        return *this;
    }

    MCBuilder & MCBuilder::setStockPriceModel(std::shared_ptr<StockModel> stockModel) {
        stockModel_ = std::move(stockModel);
        return *this;
    }

    MCBuilder & MCBuilder::setNumberGenerator(std::shared_ptr<NumberGenerarator> generator) {
        generator_ = std::move(generator);
        return *this;
    }

}
