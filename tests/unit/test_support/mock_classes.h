#ifndef MOCK_CLASSES_H
#define MOCK_CLASSES_H

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "market_data/market_data.h"
#include "option/interface_option.h"

namespace OptionPricer::Mocks {
    // Mock class for Option
    class Option final : public IOption {
    public:
        explicit Option(const std::string& ticker) : IOption(ticker) {}

        MOCK_METHOD(void, update, (), (override));
        MOCK_METHOD(std::shared_ptr<Option>, shared_from_this, (), ());
    };

    // Mock class for MarketData
    class MarketData final : public IMarketData {
    public:
        MOCK_METHOD(std::shared_ptr<const StockData>, getStockData, (const std::string& ticker), (const, override));
        MOCK_METHOD(void, addObserver, (const std::shared_ptr<MarketDataObserver>& observer), (override));
        MOCK_METHOD(void, removeObserver, (), (override));
        MOCK_METHOD(double, getR, (), (const, override));
        MOCK_METHOD(void, setR, (const double& r), (override));
    };
}

#endif //MOCK_CLASSES_H