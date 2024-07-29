#ifndef IMARKET_DATA_H
#define IMARKET_DATA_H

#include <memory>
#include <string>
#include "stock_data.h"
#include "market_data_observer.h"

namespace OptionPricer {
    class IMarketData {
    public:
        virtual ~IMarketData() = default;

        virtual void addObserver(const std::shared_ptr<MarketDataObserver>& observer) = 0;
        virtual void removeObserver() = 0;

        virtual std::shared_ptr<StockData> getStockData(const std::string& ticker) const = 0;
        virtual double getR() const = 0;
        virtual void setR(const double& r) = 0;
    };
}

#endif //IMARKET_DATA_H
