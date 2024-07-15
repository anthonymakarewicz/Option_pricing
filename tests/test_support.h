#ifndef TEST_CLASSES_H
#define TEST_CLASSES_H

#include <string>
#include "market_data.h"

namespace TestSupport {
    // Minimal Mock Option class
    class Option final : public MarketDataObserver, public std::enable_shared_from_this<Option> {
    public:
        explicit Option(std::string ticker) : MarketDataObserver(std::move(ticker)), updated_(false) {}

        void update() override { updated_ = true; }
        bool wasUpdated() const { return updated_; }
        void resetUpdated() { updated_ = false; }

    private:
        bool updated_;
    };
    // Minimal Mock MarketData class
    class MarketData {
    public:
        virtual ~MarketData() = default;
        virtual std::shared_ptr<StockData> getStockData(const std::string& ticker) const = 0;
        virtual void addObserver(std::shared_ptr<MarketDataObserver> observer) = 0;
        virtual void removeObserver(std::shared_ptr<MarketDataObserver> observer) = 0;
        virtual double getR() const = 0;
    };
}

#endif // TEST_CLASSES_H