#include "solver/monte_carlo/stock_price_model.h"

namespace OptionPricer {
    StockPriceModel::StockPriceModel(const std::string &ticker, std::shared_ptr<IMarketData> marketData) :
        ticker_(ticker), marketData_(std::move(marketData)) {}

    StockPriceModel::~StockPriceModel() = default;
}
