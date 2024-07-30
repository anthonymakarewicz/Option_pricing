#include <gtest/gtest.h>
#include <memory>
#include "option/single_path/european_option.h"
#include "market_data/market_data.h"
#include "payoff/single_strike/payoff_vanilla_call.h"

using namespace OptionPricer;

class OptionIntegrationTest : public ::testing::Test {
protected:
    OptionIntegrationTest() : K(0.0), T(0.0), payoff(nullptr), option(nullptr) {}

    static void SetUpTestSuite() {
        marketData = MarketData::getInstance();
        marketData->addStock("AAPL", 150.0, 0.2);
    }

    void SetUp () override {
        K = 100.0;
        payoff = std::make_unique<PayoffVanillaCall>(K);
        T = 1.0;
        option = std::make_shared<EuropeanOption>("AAPL", std::move(payoff), T, marketData);
        option->initialize();
    }

    double K;
    double T;
    std::unique_ptr<Payoff> payoff;
    std::shared_ptr<EuropeanOption> option;
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
    double K2 = 120.0;
    auto payoff2 = std::make_unique<PayoffVanillaCall>(K2);
    auto option2 = std::make_shared<EuropeanOption>("AAPL", std::move(payoff2), T, marketData);
    option2->initialize();

    marketData->updateStockPrice("AAPL", 160.0);
    EXPECT_DOUBLE_EQ(option->payoff(), 60.0);
    EXPECT_DOUBLE_EQ(option2->payoff(), 40.0);

    marketData->updateStockPrice("AAPL", 90.0);
    EXPECT_DOUBLE_EQ(option->payoff(), 0.0);
    EXPECT_DOUBLE_EQ(option2->payoff(), 0.0);
}
