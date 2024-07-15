#include <gtest/gtest.h>
#include <memory>
#include "../../include/market_data.h"
#include "../config/test_support.h"

// Test fixture for MarketData tests
class MarketDataTest : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        marketData = MarketData::getInstance();
        marketData->addStock("AAPL", 150.0, 0.2, 0.01);
        observer = std::make_shared<TestSupport::Option>("AAPL");
        marketData->addObserver(observer);
    }

    static void TearDownTestSuite() {
        // Reset the state if necessary
        marketData.reset();
        observer.reset();
        //MarketData::instance_ = nullptr; // Assuming this is allowed in your implementation to reset the singleton
    }

    void TearDown() override {
        observer->resetUpdated();
    }

    static std::shared_ptr<MarketData> marketData;
    static std::shared_ptr<TestSupport::Option> observer;
    //std::string ticker;
};

// Static member initialization to avoid u
std::shared_ptr<MarketData> MarketDataTest::marketData = nullptr;
std::shared_ptr<TestSupport::Option> MarketDataTest::observer = nullptr;


TEST_F(MarketDataTest, SingletonInstance) {
    auto instance1 = MarketData::getInstance();
    auto instance2 = MarketData::getInstance();
    EXPECT_EQ(instance1, instance2); // Both should point to the same instance
}

TEST_F(MarketDataTest, NotifyObserver) {
    marketData->notifyObserver("AAPL");
    EXPECT_TRUE(observer->wasUpdated());
}

TEST_F(MarketDataTest, NotifyAllObservers) {
    auto observer2 = std::make_shared<TestSupport::Option>("AAPL");
    marketData->addObserver(observer2);

    marketData->notifyObservers();
    EXPECT_TRUE(observer->wasUpdated());
    EXPECT_TRUE(observer2->wasUpdated());

    marketData->removeObserver(observer2);
    observer->resetUpdated();
    observer2->resetUpdated();

    marketData->notifyObservers();
    EXPECT_FALSE(observer2->wasUpdated());
}

TEST_F(MarketDataTest, AddAndUpdateStockData) {
    auto stockData = marketData->getStockData("AAPL");
    EXPECT_DOUBLE_EQ(stockData->getPrice(), 150.0);
    EXPECT_DOUBLE_EQ(stockData->getSigma(), 0.2);
    EXPECT_TRUE(stockData->getCoupon().has_value());
    EXPECT_DOUBLE_EQ(stockData->getCoupon().value(), 0.01);

    marketData->updateStockPrice("AAPL", 160.0);
    marketData->updateStockSigma("AAPL", 0.25);
    marketData->updateStockCoupon("AAPL", 0.02);

    EXPECT_DOUBLE_EQ(stockData->getPrice(), 160.0);
    EXPECT_DOUBLE_EQ(stockData->getSigma(), 0.25);
    EXPECT_TRUE(stockData->getCoupon().has_value());
    EXPECT_DOUBLE_EQ(stockData->getCoupon().value(), 0.02);

    EXPECT_TRUE(observer->wasUpdated());
}

TEST_F(MarketDataTest, UpdateNonExistentStock) {
    EXPECT_THROW(auto stockData = marketData->getStockData("MSFT"), std::invalid_argument);

    // Ensure exception is thrown when updating non-existent stock data
    EXPECT_THROW(marketData->updateStockPrice("MSFT", 200.0), std::invalid_argument);
    EXPECT_THROW(marketData->updateStockSigma("MSFT", 0.3), std::invalid_argument);
    EXPECT_THROW(marketData->updateStockCoupon("MSFT", 0.04), std::invalid_argument);
}

TEST_F(MarketDataTest, RiskFreeRate) {
    marketData->setR(0.05);
    EXPECT_DOUBLE_EQ(marketData->getR(), 0.05);

    marketData->setR(0.03);
    EXPECT_DOUBLE_EQ(marketData->getR(), 0.03);
}


class StockDataTest : public ::testing::Test {};

TEST_F(StockDataTest, InvalidStockData) {
    EXPECT_THROW(StockData(-150.0, 0.2, 0.01), std::invalid_argument);
    EXPECT_THROW(StockData(150.0, -0.2, 0.01), std::invalid_argument);
    EXPECT_THROW(StockData(150.0, 0.2, -0.01), std::invalid_argument);
    EXPECT_THROW(StockData(150.0, 0.2, 1.5), std::invalid_argument);
}
