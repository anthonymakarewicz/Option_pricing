#ifndef STOCK_PRICE_MODEL_H
#define STOCK_PRICE_MODEL_H

#include <string>
#include "market_data/interface_market_data.h"

namespace OptionPricer {
    class StockPriceModel {
    public:
        StockPriceModel(const std::string& ticker, std::shared_ptr<IMarketData> marketData);
        virtual ~StockPriceModel();
        [[nodiscard]] virtual double simulate_price(const double& maturity) const = 0;

    protected:
        std::string ticker_;
        std::shared_ptr<IMarketData> marketData_;
    };
}

#endif //STOCK_PRICE_MODEL_H
