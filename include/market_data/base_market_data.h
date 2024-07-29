#ifndef BASE_MARKET_DATA_H
#define BASE_MARKET_DATA_H

#include <memory>
#include <string>
#include "stock_data.h"
#include "market_data_observer.h"

namespace OptionPricer {
    // Interface injection for production and mock object for unit test
    class IMarketData {
    public:
        virtual ~IMarketData();

        virtual void addObserver(const std::shared_ptr<MarketDataObserver>& observer) = 0;
        virtual void removeObserver() = 0;

        [[nodiscard]] virtual std::shared_ptr<StockData> getStockData(const std::string& ticker) const = 0;
        [[nodiscard]] virtual double getR() const = 0;
        virtual void setR(const double& r) = 0;
    };
}

#endif //BASE_MARKET_DATA_H
