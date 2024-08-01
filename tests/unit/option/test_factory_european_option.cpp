#include <gtest/gtest.h>
#include "option/single_path/factory_european_option.h"
#include "market_data/market_data.h"

using namespace OptionPricer;

class FactoryTest : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        marketData = MarketData::getInstance();
        marketData->addStock("AAPL", 150.0, 0.2);
    }

    static std::shared_ptr<MarketData> marketData;
};

std::shared_ptr<MarketData> FactoryTest::marketData = nullptr;

TEST_F(FactoryTest, CreateValidCallOption) {
    ParameterObject params;
    params.setParameter("ticker", "AAPL");
    params.setParameter("T", 1.0);
    params.setParameter("K", 100.0);

    EuropeanOptionFactory factory;
    auto option = factory.createCallOption(params);

    ASSERT_NE(option, nullptr);
    EXPECT_EQ(option->getType(), "OptionPricer::EuropeanOption");
}

TEST_F(FactoryTest, CreateValidPutOption) {
    ParameterObject params;
    params.setParameter("ticker", "AAPL");
    params.setParameter("T", 1.0);
    params.setParameter("K", 100.0);

    EuropeanOptionFactory factory;
    auto option = factory.createPutOption(params);

    ASSERT_NE(option, nullptr);
    EXPECT_EQ(option->getType(), "OptionPricer::EuropeanOption");
}

TEST_F(FactoryTest, CreateOptionWithMissingParameter) {
    ParameterObject params;
    params.setParameter("ticker", "AAPL"); // Invalid ticker symbol
    params.setParameter("T", 1.0);
    // Missing "K" parameter

    EuropeanOptionFactory factory;
    EXPECT_THROW(auto option = factory.createCallOption(params), std::invalid_argument);
}

TEST_F(FactoryTest, CreateOptionWithInvalidTicker) {
    ParameterObject params;
    params.setParameter("ticker", "XXX");
    params.setParameter("T", 1.0);
    params.setParameter("K", 100.0);

    EuropeanOptionFactory factory;
    EXPECT_THROW(auto option = factory.createCallOption(params), std::invalid_argument);
    EXPECT_THROW(auto option = factory.createPutOption(params), std::invalid_argument);
}

TEST_F(FactoryTest, CreateOptionWithInvalidStrike) {
    ParameterObject params;
    params.setParameter("ticker", "AAPL");
    params.setParameter("T", 1.0);
    params.setParameter("K", -100.0);

    EuropeanOptionFactory factory;
    EXPECT_THROW(auto option = factory.createCallOption(params), std::invalid_argument);
    EXPECT_THROW(auto option = factory.createPutOption(params), std::invalid_argument);
}
