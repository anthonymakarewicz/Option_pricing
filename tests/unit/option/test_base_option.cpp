#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "option/base_option.h"
#include "payoff/single_strike/payoff_vanilla_call.h"
#include "../test_support/mock_classes.h"


/*

using namespace OptionPricer;
using namespace testing;

// Create a test class deriving from Option to test the base functionality
class TestOption : public Option {
public:
    TestOption(const std::string& ticker, std::unique_ptr<Payoff> payoff,
        const double& T, std::shared_ptr<IMarketData> marketData)
        : Option(ticker, std::move(payoff), T) {
        marketData_ = marketData;
    }

    double calc_price() const override {
        return 42.0; // Example return value for testing
    }
private:
    std::shared_ptr<IMarketData> marketData_;
};

// Test fixture for Option tests
class OptionTest : public Test {
protected:
    void SetUp() override {
        ticker = "AAPL";
        T = 1.0;
        payoff = std::make_unique<PayoffVanillaCall>(100.0);
        mockMarketData = std::make_shared<Mocks::MarketData>();
    }

    std::string ticker;
    double T;
    std::unique_ptr<Payoff> payoff;
    std::shared_ptr<Mocks::MarketData> mockMarketData;
};

TEST_F(OptionTest, ConstructorTest) {
    EXPECT_CALL(*mockMarketData, getStockData(ticker))
        .Times(1)
        .WillOnce(Return(std::make_shared<StockData>(150.0, 0.2, std::nullopt)));
    EXPECT_CALL(*mockMarketData, addObserver(_))
        .Times(1);

    TestOption option(ticker, std::move(payoff), T, mockMarketData);

    // Check if the Option object is constructed properly
    EXPECT_EQ(option.getType(), "TestOption");
}

TEST_F(OptionTest, UpdateTest) {
    EXPECT_CALL(*mockMarketData, getStockData(ticker))
        .Times(1)
        .WillOnce(Return(std::make_shared<StockData>(150.0, 0.2, std::nullopt)));
    EXPECT_CALL(*mockMarketData, addObserver(_))
        .Times(1);

    TestOption option(ticker, std::move(payoff), T, mockMarketData);

    EXPECT_CALL(*mockMarketData, getStockData(ticker))
        .Times(1)
        .WillOnce(Return(std::make_shared<StockData>(160.0, 0.25, 0.02)));

    option.update();

    // Verify that the update method works correctly
    // This will depend on the actual implementation of the update method
}

TEST_F(OptionTest, CopyConstructorTest) {
    EXPECT_CALL(*mockMarketData, getStockData(ticker))
        .Times(1)
        .WillOnce(Return(std::make_shared<StockData>(150.0, 0.2, std::nullopt)));
    EXPECT_CALL(*mockMarketData, addObserver(_))
        .Times(1);

    TestOption option1(ticker, std::move(payoff), T, mockMarketData);
    TestOption option2 = option1;

    // Verify that the copy constructor works correctly
    EXPECT_EQ(option2.getType(), "TestOption");
}

TEST_F(OptionTest, MoveConstructorTest) {
    EXPECT_CALL(*mockMarketData, getStockData(ticker))
        .Times(1)
        .WillOnce(Return(std::make_shared<StockData>(150.0, 0.2, std::nullopt)));
    EXPECT_CALL(*mockMarketData, addObserver(_))
        .Times(1);

    TestOption option1(ticker, std::move(payoff), T, mockMarketData);
    TestOption option2 = std::move(option1);

    // Verify that the move constructor works correctly
    EXPECT_EQ(option2.getType(), "TestOption");
}

TEST_F(OptionTest, AssignmentOperatorTest) {
    EXPECT_CALL(*mockMarketData, getStockData(ticker))
        .Times(2)
        .WillRepeatedly(Return(std::make_shared<StockData>(150.0, 0.2, std::nullopt)));
    EXPECT_CALL(*mockMarketData, addObserver(_))
        .Times(2);

    TestOption option1(ticker, std::move(payoff), T, mockMarketData);

    auto payoff2 = std::make_unique<PayoffVanillaCall>(100.0);
    TestOption option2(ticker, std::move(payoff2), T, mockMarketData);

    option2 = option1;

    // Verify that the assignment operator works correctly
    EXPECT_EQ(option2.getType(), "TestOption");
}
*/
