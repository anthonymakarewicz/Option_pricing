#ifndef MOCK_CLASSES_H
#define MOCK_CLASSES_H

#include <gmock/gmock.h>
#include "test_support.h"

// Nested namespace C++17
namespace TestSupport::MockImplementations {
    // Mock class for MarketData using Google Mock
    class MockMarketData final : public TestSupport::MarketData {
    public:
        MOCK_METHOD(std::shared_ptr<StockData>, getStockData, (const std::string& ticker), (const, override));
        MOCK_METHOD(void, addObserver, (std::shared_ptr<MarketDataObserver> observer), (override));
        MOCK_METHOD(void, removeObserver, (std::shared_ptr<MarketDataObserver> observer), (override));
        MOCK_METHOD(double, getR, (), (const, override));
    };
}

#endif // MOCK_CLASSES_H