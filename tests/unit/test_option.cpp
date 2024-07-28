#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <option/options/single_path/european_option.h>
#include "option/options/base_option.h"
#include "payoff/single_strike/vanilla/payoff_vanilla_call.h"
#include "test_support/mock_classes.h"

using namespace testing;

class OptionTest : public ::testing::Test {
protected:
    OptionTest() : T(0.0) {}

    void SetUp() override {
        ticker = "AAPL";
        T = 1.0;
        payoff = std::make_unique<PayoffVanillaCall>(100.0);
        mockMarketData = std::make_shared<Mocks::MarketData>();
        //MarketData::instance_ = mockMarketData; // Point the MarketData singleton to the mock
    }

    void TearDown() override {
        //MarketData::instance_ = nullptr; // Reset the singleton to avoid interference between tests
    }

    std::string ticker;
    double T;
    std::unique_ptr<Payoff> payoff;
    std::shared_ptr<Mocks::MarketData> mockMarketData;
};

// Test constructor and initialization
TEST_F(OptionTest, ConstructorTest) {
    EXPECT_CALL(*mockMarketData, getStockData(ticker)).Times(1).WillOnce(Return(std::make_shared<StockData>(150.0, 0.2, 0.01)));
    EXPECT_CALL(*mockMarketData, addObserver(_)).Times(1);

    std::shared_ptr<Option> option = std::make_shared<EuropeanOption>(ticker, std::move(payoff), T);

    EXPECT_EQ(option->calc_price(), 0.0); // Assuming the initial calc_price is 0.0
}

// Test update method
TEST_F(OptionTest, UpdateTest) {
    EXPECT_CALL(*mockMarketData, getStockData(ticker)).Times(1).WillOnce(Return(std::make_shared<StockData>(150.0, 0.2, 0.01)));
    EXPECT_CALL(*mockMarketData, addObserver(_)).Times(1);
    EXPECT_CALL(*mockMarketData, getR()).Times(1).WillOnce(Return(0.05));

    std::shared_ptr<Option> option = std::make_shared<EuropeanOption>(ticker, std::move(payoff), T);

    EXPECT_CALL(*mockMarketData, getStockData(ticker)).Times(1).WillOnce(Return(std::make_shared<StockData>(160.0, 0.25, 0.02)));

    option->update();
    // Verify if the update method works correctly
    // You might want to add more specific checks based on the implementation of calc_price
}

// Test copy constructor
TEST_F(OptionTest, CopyConstructorTest) {
    EXPECT_CALL(*mockMarketData, getStockData(ticker)).Times(1).WillOnce(Return(std::make_shared<StockData>(150.0, 0.2, 0.01)));
    EXPECT_CALL(*mockMarketData, addObserver(_)).Times(1);

    std::shared_ptr<Option> option1 = std::make_shared<SinglePathOption>(ticker, std::move(payoff), T);

    // Create another payoff object for the copy constructor
    auto payoff2 = std::make_unique<PayoffVanillaCall>(100.0);
    EuropeanOption option2 = *dynamic_cast<EuropeanOption*>(option1.get());

    EXPECT_EQ(option2.calc_price(), 0.0); // Assuming the initial calc_price is 0.0
}

// Test move constructor
TEST_F(OptionTest, MoveConstructorTest) {
    EXPECT_CALL(*mockMarketData, getStockData(ticker)).Times(1).WillOnce(Return(std::make_shared<StockData>(150.0, 0.2, 0.01)));
    EXPECT_CALL(*mockMarketData, addObserver(_)).Times(1);

    std::shared_ptr<Option> option1 = std::make_shared<EuropeanOption>(ticker, std::move(payoff), T);

    EuropeanOption option2 = std::move(*dynamic_cast<EuropeanOption*>(option1.get()));

    EXPECT_EQ(option2.calc_price(), 0.0); // Assuming the initial calc_price is 0.0
}

// Test assignment operator
TEST_F(OptionTest, AssignmentOperatorTest) {
    EXPECT_CALL(*mockMarketData, getStockData(ticker)).Times(2).WillRepeatedly(Return(std::make_shared<StockData>(150.0, 0.2, 0.01)));
    EXPECT_CALL(*mockMarketData, addObserver(_)).Times(2);

    std::shared_ptr<Option> option1 = std::make_shared<SinglePathOption>(ticker, std::move(payoff), T);

    auto payoff2 = std::make_unique<PayoffVanillaCall>(100.0);
    std::shared_ptr<Option> option2 = std::make_shared<SinglePathOption>(ticker, std::move(payoff2), T);

    *dynamic_cast<SinglePathOption*>(option2.get()) = *dynamic_cast<SinglePathOption*>(option1.get());

    EXPECT_EQ(option2->calc_price(), 0.0); // Assuming the initial calc_price is 0.0
}
