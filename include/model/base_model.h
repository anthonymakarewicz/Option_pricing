#ifndef STOCK_PRICE_MODEL_H
#define STOCK_PRICE_MODEL_H

#include <string>
#include "market_data/interface_market_data.h"

namespace OptionPricer {

    class StockModel {
    public:
        StockModel(const std::string& ticker, std::shared_ptr<IMarketData> marketData);
        virtual ~StockModel();

        [[nodiscard]] virtual double simulatePriceAtMaturity(const double& T, const double& z) const = 0;
        [[nodiscard]] virtual double simulateStepPrice(const double& dt, const double& z) const = 0;

    protected:
        std::string ticker_;
        std::shared_ptr<const StockData> stockData_; // Cache StockData for consultation
        std::shared_ptr<IMarketData> marketData_;
    };

}

#endif //STOCK_PRICE_MODEL_H
