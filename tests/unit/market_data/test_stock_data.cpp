#include "gtest/gtest.h"
#include "market_data/stock_data.h"

using namespace OptionPricer;

class StockDataTest : public ::testing::Test {};

TEST_F(StockDataTest, InvalidStockData) {
    EXPECT_THROW(StockData(-150.0, 0.2, 0.01), std::invalid_argument);
    EXPECT_THROW(StockData(150.0, -0.2, 0.01), std::invalid_argument);
    EXPECT_THROW(StockData(150.0, 0.2, -0.01), std::invalid_argument);
    EXPECT_THROW(StockData(150.0, 0.2, 1.5), std::invalid_argument);
}

TEST_F(StockDataTest, EqualityStockData) {
    StockData stock1 (150.0, 0.2, 0.01);
    StockData stock2 (150.0, 0.2, 0.01);
    StockData stock3 (100.0, 0.2, 0.01);
    StockData stock4 (100.0, 0.3, 0.01);
    StockData stock5 (150.0, 0.2);

    EXPECT_TRUE(stock1 == stock2);
    EXPECT_TRUE(stock1 != stock3);
    EXPECT_TRUE(stock1 != stock4);
    EXPECT_TRUE(stock1 != stock5);
}