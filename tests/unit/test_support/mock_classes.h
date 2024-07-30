#ifndef MOCK_CLASSES_H
#define MOCK_CLASSES_H

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "market_data/market_data.h"

namespace OptionPricer::Mocks {
    // Minimal Mock Option class
    class Option final : public MarketDataObserver, public std::enable_shared_from_this<Option> {
    public:
        explicit Option(const std::string& ticker) : MarketDataObserver(ticker), updated_(false) {}

        void update() override { updated_ = true; }
        bool wasUpdated() const { return updated_; }
        void resetUpdated() { updated_ = false; }

    private:
        bool updated_;
    };

    // Mock class for MarketData using Google Mock
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