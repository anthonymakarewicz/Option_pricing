
#include <gtest/gtest.h>
#include "market_data.h"



// Test adding and retrieving StockData
TEST(MarketDataTests, StockData) {
    MarketData marketData;
    marketData.addData<StockData>("AAPL", 150.0, 0.2); // Add Apple stock data

    // Retrieve the added stock data and verify its content
    auto stockData = marketData.getData<StockData>("AAPL");
    EXPECT_THROW(marketData.getData<StockData>("NONEXISTENT"), std::runtime_error);
    ASSERT_NE(stockData, nullptr); // Ensure the data is not null

    EXPECT_DOUBLE_EQ(stockData->getPrice(), 150.0);
    EXPECT_DOUBLE_EQ(stockData->getSigma(), 0.2);

    stockData->updatePrice(155.0); // Update the price
    stockData->updateSigma(0.25); // Update the volatility

    // Verify the updated data
    EXPECT_DOUBLE_EQ(stockData->getPrice(), 155.0);
    EXPECT_DOUBLE_EQ(stockData->getSigma(), 0.25);

    // Verify the synchronization worked as expected
    auto stockData2 = marketData.getData<StockData>("AAPL");

    EXPECT_DOUBLE_EQ(stockData2->getPrice(), 155.0);
    EXPECT_DOUBLE_EQ(stockData2->getSigma(), 0.25);
}


TEST(MarketDataTests, InterestRateData) {
    MarketData marketData;
    marketData.addData<InterestRateData>("LIBOR",0.05); // Add Apple stock data

    // Retrieve the added stock data and verify its content
    auto irData = marketData.getData<InterestRateData>("LIBOR");
    EXPECT_THROW(marketData.getData<StockData>("NONEXISTENT"), std::runtime_error);
    ASSERT_NE(irData, nullptr); // Ensure the data is not null

    EXPECT_DOUBLE_EQ(irData->getRate(), 0.05);

    irData->updateRate(0.10); // Update the price

    // Verify the updated data
    EXPECT_DOUBLE_EQ(irData->getRate(), 0.10);

    // Verify the synchronization worked as expected
    auto irData2 = marketData.getData<InterestRateData>("LIBOR");

    EXPECT_DOUBLE_EQ(irData2->getRate(), 0.10);
}



