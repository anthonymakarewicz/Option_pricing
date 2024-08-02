#include <gtest/gtest.h>
#include <memory>
#include "option/single_path/factory_european_option.h"
#include "market_data/market_data.h"

using namespace OptionPricer;

class OptionIntegrationTest : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        marketData = MarketData::getInstance();
        marketData->addStock("AAPL", 150.0, 0.2);
    }

    void SetUp () override {
        std::string ticker = "AAPL";
        double K = 100.0;
        double T = 1.0;

        params.setParameter("ticker", ticker);
        params.setParameter("K", K);
        params.setParameter("T", T);

        option = factory.createCallOption(params);
    }

    ParameterObject params;
    EuropeanOptionFactory factory;
    std::shared_ptr<Option> option;
    static std::shared_ptr<MarketData> marketData;
};

std::shared_ptr<MarketData> OptionIntegrationTest::marketData = nullptr;

TEST_F(OptionIntegrationTest, ConstructorTest) {
    EXPECT_EQ(option->getType(), "OptionPricer::EuropeanOption");
    EXPECT_NO_THROW(option->payoff());
    EXPECT_DOUBLE_EQ(option->payoff(), 50.0);
}

TEST_F(OptionIntegrationTest, UpdateStockPriceTest) {
    marketData->updateStockPrice("AAPL", 170.0);
    EXPECT_DOUBLE_EQ(option->payoff(), 70.0);

    marketData->updateStockPrice("AAPL", 50.0);
    EXPECT_DOUBLE_EQ(option->payoff(), 0.0);
}

// Additional test to check observer interaction
TEST_F(OptionIntegrationTest, ObserverInteractionTest) {
    // Create another option to observe the market data
    params.setParameter("K", 120.0);

    auto option2 = factory.createCallOption(params);

    marketData->updateStockPrice("AAPL", 160.0);
    EXPECT_DOUBLE_EQ(option->payoff(), 60.0);
    EXPECT_DOUBLE_EQ(option2->payoff(), 40.0);

    marketData->updateStockPrice("AAPL", 90.0);
    EXPECT_DOUBLE_EQ(option->payoff(), 0.0);
    EXPECT_DOUBLE_EQ(option2->payoff(), 0.0);
}
