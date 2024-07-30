#include <gtest/gtest.h>
#include <memory>
#include "market_data/market_data.h"
#include "../test_support/mock_classes.h"

using namespace OptionPricer;

// Test fixture for MarketData tests
class MarketDataTest : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        marketData = MarketData::getInstance();
        marketData->addStock("AAPL", 150.0, 0.2, 0.01);
        observer = std::make_shared<Mocks::Option>("AAPL");
        marketData->addObserver(observer);
    }

    static void TearDownTestSuite() {
        // Reset the state if necessary
        marketData.reset();
        observer.reset();
        //MarketData::instance_ = nullptr; // Assuming this is allowed in your implementation to reset the singleton
    }

    static std::shared_ptr<MarketData> marketData;
    static std::shared_ptr<Mocks::Option> observer;
    //std::string ticker;
};

// Static member initialization to avoid undefined behaviour
std::shared_ptr<MarketData> MarketDataTest::marketData = nullptr;
std::shared_ptr<Mocks::Option> MarketDataTest::observer = nullptr;

TEST_F(MarketDataTest, SingletonInstance) {
    auto instance1 = MarketData::getInstance();
    auto instance2 = MarketData::getInstance();
    EXPECT_EQ(instance1, instance2); // Both should point to the same instance
}

TEST_F(MarketDataTest, NotifyObserver) {
    EXPECT_CALL(*observer, update()).Times(1);
    marketData->notifyObserver("AAPL");
}

TEST_F(MarketDataTest, RemoveObserver) {
    EXPECT_CALL(*observer, update()).Times(0);
    observer.reset();
    marketData->removeObserver();
    marketData->notifyObserver("AAPL");
}

TEST_F(MarketDataTest, NotifyAllObservers) {
    auto observer2 = std::make_shared<Mocks::Option>("AAPL");
    marketData->addObserver(observer2);

    EXPECT_CALL(*observer, update()).Times(1);
    EXPECT_CALL(*observer2, update()).Times(1);
    marketData->notifyObservers();
}

TEST_F(MarketDataTest, GetStockData) {
    auto stockData = marketData->getStockData("AAPL");

    EXPECT_DOUBLE_EQ(stockData->getPrice(), 150.0);
    EXPECT_DOUBLE_EQ(stockData->getSigma(), 0.2);
    EXPECT_TRUE(stockData->getCoupon().has_value());
    EXPECT_DOUBLE_EQ(stockData->getCoupon().value(), 0.01);
}

TEST_F(MarketDataTest, UpdateStockData) {
    EXPECT_CALL(*observer, update()).Times(3);
    auto stockData = marketData->getStockData("AAPL");

    marketData->updateStockPrice("AAPL", 160.0);
    marketData->updateStockSigma("AAPL", 0.25);
    marketData->updateStockCoupon("AAPL", 0.02);

    EXPECT_DOUBLE_EQ(stockData->getPrice(), 160.0);
    EXPECT_DOUBLE_EQ(stockData->getSigma(), 0.25);
    EXPECT_TRUE(stockData->getCoupon().has_value());
    EXPECT_DOUBLE_EQ(stockData->getCoupon().value(), 0.02);
}

TEST_F(MarketDataTest, UpdateNonExistentStock) {
    EXPECT_THROW(auto stockData = marketData->getStockData("MSFT"), std::invalid_argument);

    EXPECT_THROW(marketData->updateStockPrice("MSFT", 200.0), std::invalid_argument);
    EXPECT_THROW(marketData->updateStockSigma("MSFT", 0.3), std::invalid_argument);
    EXPECT_THROW(marketData->updateStockCoupon("MSFT", 0.04), std::invalid_argument);
}

TEST_F(MarketDataTest, RiskFreeRate) {
    EXPECT_CALL(*observer, update()).Times(2);

    marketData->setR(0.10);
    EXPECT_DOUBLE_EQ(marketData->getR(), 0.10);
    marketData->setR(0.05);
    EXPECT_DOUBLE_EQ(marketData->getR(), 0.05);
}
