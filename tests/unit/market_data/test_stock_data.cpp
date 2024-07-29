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