#include "model/base_model.h"

namespace OptionPricer {

    StockModel::StockModel(const std::string &ticker, std::shared_ptr<IMarketData> marketData)
    : ticker_(ticker), marketData_(std::move(marketData)) {
        stockData_ = marketData_->getStockData(ticker);
    }

    StockModel::~StockModel() = default;

}