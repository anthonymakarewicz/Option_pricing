#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "option/base_option.h"
#include "payoff/single_strike/payoff_vanilla_call.h"
#include "../test_support/mock_classes.h"

using namespace OptionPricer;
using namespace testing;

// Create a test class deriving from Option to test the base functionality
class TestOption final: public Option {
public:
    TestOption(const std::string& ticker, std::unique_ptr<Payoff> payoff,
        const double& T, std::shared_ptr<IMarketData> marketData)
        : Option(ticker, std::move(payoff), T, std::move(marketData)) {}

    double calc_price() const override {
        return 42.0; // Example return value for testing
    }
};

// Test fixture for Option tests
class OptionTest : public Test {
protected:
    OptionTest() : T(0.0), K(0.0),  payoff(nullptr), mockMarketData(nullptr) {}

    void SetUp() override {
        ticker = "AAPL";
        T = 1.0;
        K = 100.0;
        payoff = std::make_unique<PayoffVanillaCall>(K);
        mockMarketData = std::make_shared<Mocks::MarketData>();
    }

    std::string ticker;
    double T;
    double K;
    std::unique_ptr<Payoff> payoff;
    std::shared_ptr<Mocks::MarketData> mockMarketData;
};

TEST_F(OptionTest, ConstructorTest) {
    EXPECT_CALL(*mockMarketData, getStockData(ticker))
        .Times(1)
        .WillOnce(Return(std::make_shared<StockData>(150.0, 0.2, std::nullopt)));
    EXPECT_CALL(*mockMarketData, removeObserver())
        .Times(1);

    TestOption option (ticker, std::move(payoff), T, mockMarketData);

    // Check if the Option object is constructed properly
    EXPECT_EQ(option.getType(), "TestOption");
}

TEST_F(OptionTest, SharedPtrConstructorTest) {
    EXPECT_CALL(*mockMarketData, getStockData(ticker))
        .Times(1)
        .WillOnce(Return(std::make_shared<StockData>(150.0, 0.2, std::nullopt)));
    EXPECT_CALL(*mockMarketData, addObserver(_))
        .Times(1);
    EXPECT_CALL(*mockMarketData, removeObserver())
        .Times(1);

    std::shared_ptr<TestOption> optionPtr = std::make_shared<TestOption>(ticker, std::move(payoff), T, mockMarketData);
    optionPtr->initialize();

    // Check if the Option object is constructed properly
    EXPECT_EQ(optionPtr->getType(), "TestOption");
}

TEST_F(OptionTest, CalculatePriceTest) {
    EXPECT_CALL(*mockMarketData, getStockData(ticker))
        .Times(1)
        .WillOnce(Return(std::make_shared<StockData>(150.0, 0.2, std::nullopt)));
    EXPECT_CALL(*mockMarketData, removeObserver())
        .Times(1);

    TestOption option(ticker, std::move(payoff), T, mockMarketData);

    // Check if the Option object is constructed properly
    EXPECT_EQ(option.calc_price(), 42.0);
}

TEST_F(OptionTest, PayoffTest) {
    EXPECT_CALL(*mockMarketData, getStockData(ticker))
        .Times(2)
        .WillRepeatedly(Return(std::make_shared<StockData>(150.0, 0.2, std::nullopt)));
    EXPECT_CALL(*mockMarketData, removeObserver())
    .Times(1);

    TestOption option(ticker, std::move(payoff), T, mockMarketData);

    // Check if the Option object is constructed properly
    EXPECT_EQ(option.payoff(), 50.0);
    EXPECT_EQ(option.payoff(150.0), 50.0);
}

TEST_F(OptionTest, SharedPtrMoveTest) {
    EXPECT_CALL(*mockMarketData, getStockData(ticker))
        .Times(1)
        .WillRepeatedly(Return(std::make_shared<StockData>(150.0, 0.2, std::nullopt)));
    EXPECT_CALL(*mockMarketData, addObserver(_))
        .Times(1);
    EXPECT_CALL(*mockMarketData, removeObserver())
        .Times(1);

    std::shared_ptr<TestOption> optionPtr1 = std::make_shared<TestOption>(ticker, std::move(payoff), T, mockMarketData);
    optionPtr1->initialize();
    std::shared_ptr<TestOption> optionPtr2 = std::move(optionPtr1);

    // Verify that the move constructor works correctly
    EXPECT_EQ(optionPtr1.get(), nullptr);
}