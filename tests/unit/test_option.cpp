#ifndef TEST_OPTION_CPP
#define TEST_OPTION_CPP

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../../include/option.h"
#include "../../include/payoff.h"
#include "../config/test_support.h"
#include "../config/mock_classes.h"

using namespace ::testing;
using namespace TestSupport::MockImplementations;

class OptionTest : public Test {
protected:
    void SetUp() override {
        ticker = "AAPL";
        T = 1.0;
        payoff = std::make_unique<PayoffCall>(100.0);
        mockMarketData = std::make_shared<MockMarketData>();
        //MarketData::instance_ = mockMarketData; // Point the MarketData singleton to the mock
    }

    void TearDown() override {
        //MarketData::instance_ = nullptr; // Reset the singleton to avoid interference between tests
    }

    std::string ticker;
    double T;
    std::unique_ptr<Payoff> payoff;
    std::shared_ptr<MockMarketData> mockMarketData;
};

// Test constructor and initialization
TEST_F(OptionTest, ConstructorTest) {
    EXPECT_CALL(*mockMarketData, getStockData(ticker)).Times(1).WillOnce(Return(std::make_shared<StockData>(150.0, 0.2, 0.01)));
    EXPECT_CALL(*mockMarketData, addObserver(_)).Times(1);

    std::shared_ptr<Option> option = std::make_shared<VanillaOption>(ticker, std::move(payoff), T);

    EXPECT_EQ(option->calc_price(), 0.0); // Assuming the initial calc_price is 0.0
}

// Test update method
TEST_F(OptionTest, UpdateTest) {
    EXPECT_CALL(*mockMarketData, getStockData(ticker)).Times(1).WillOnce(Return(std::make_shared<StockData>(150.0, 0.2, 0.01)));
    EXPECT_CALL(*mockMarketData, addObserver(_)).Times(1);
    EXPECT_CALL(*mockMarketData, getR()).Times(1).WillOnce(Return(0.05));

    std::shared_ptr<Option> option = std::make_shared<VanillaOption>(ticker, std::move(payoff), T);

    EXPECT_CALL(*mockMarketData, getStockData(ticker)).Times(1).WillOnce(Return(std::make_shared<StockData>(160.0, 0.25, 0.02)));

    option->update();
    // Verify if the update method works correctly
    // You might want to add more specific checks based on the implementation of calc_price
}

// Test copy constructor
TEST_F(OptionTest, CopyConstructorTest) {
    EXPECT_CALL(*mockMarketData, getStockData(ticker)).Times(1).WillOnce(Return(std::make_shared<StockData>(150.0, 0.2, 0.01)));
    EXPECT_CALL(*mockMarketData, addObserver(_)).Times(1);

    std::shared_ptr<Option> option1 = std::make_shared<VanillaOption>(ticker, std::move(payoff), T);

    // Create another payoff object for the copy constructor
    auto payoff2 = std::make_unique<PayoffCall>(100.0);
    VanillaOption option2 = *dynamic_cast<VanillaOption*>(option1.get());

    EXPECT_EQ(option2.calc_price(), 0.0); // Assuming the initial calc_price is 0.0
}

// Test move constructor
TEST_F(OptionTest, MoveConstructorTest) {
    EXPECT_CALL(*mockMarketData, getStockData(ticker)).Times(1).WillOnce(Return(std::make_shared<StockData>(150.0, 0.2, 0.01)));
    EXPECT_CALL(*mockMarketData, addObserver(_)).Times(1);

    std::shared_ptr<Option> option1 = std::make_shared<VanillaOption>(ticker, std::move(payoff), T);

    VanillaOption option2 = std::move(*dynamic_cast<VanillaOption*>(option1.get()));

    EXPECT_EQ(option2.calc_price(), 0.0); // Assuming the initial calc_price is 0.0
}

// Test assignment operator
TEST_F(OptionTest, AssignmentOperatorTest) {
    EXPECT_CALL(*mockMarketData, getStockData(ticker)).Times(2).WillRepeatedly(Return(std::make_shared<StockData>(150.0, 0.2, 0.01)));
    EXPECT_CALL(*mockMarketData, addObserver(_)).Times(2);

    std::shared_ptr<Option> option1 = std::make_shared<VanillaOption>(ticker, std::move(payoff), T);

    auto payoff2 = std::make_unique<PayoffCall>(100.0);
    std::shared_ptr<Option> option2 = std::make_shared<VanillaOption>(ticker, std::move(payoff2), T);

    *dynamic_cast<VanillaOption*>(option2.get()) = *dynamic_cast<VanillaOption*>(option1.get());

    EXPECT_EQ(option2->calc_price(), 0.0); // Assuming the initial calc_price is 0.0
}

#endif //TEST_OPTION_CPP