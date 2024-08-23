#include "model/base_model.h"

namespace OptionPricer {

    StockModel::StockModel(const std::string &ticker, std::shared_ptr<IMarketData> marketData,
                           std::shared_ptr<NumberGenerator> generator)
    : ticker_(ticker), marketData_(std::move(marketData)), generator_(std::move(generator)) {
        stockData_ = marketData_->getStockData(ticker);
    }

    StockModel::~StockModel() = default;

    unsigned int StockModel::getSteps() const {
        return generator_->getDim();
    }

    std::shared_ptr<NumberGenerator> StockModel::getGenerator() const {
            return generator_;
    }

    double StockModel::simulatePriceBackward(const double &S_next,
                                             const double &t_j,
                                             const double &t_jp1) const {
        throw std::logic_error("Backward simulation not supported for this model.");
    }

}
