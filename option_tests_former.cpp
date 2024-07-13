
// Test Suite for Option Class

#include <gtest/gtest.h>

#include "option.h"
#include "payoff.h"
#include "market_data.h"

/* Tests the move semantics of the Option class to ensure that moving an Option object
   leaves the source object in a valid, but "empty" state, and that the target object
   correctly acquires the source's resources. */

class OptionTest : public ::testing::Test {
protected:
    std::shared_ptr<MarketData> marketData;

    void SetUp() override {
        marketData = std::make_shared<MarketData>();
        // Assume addData is a method to add stock data
        marketData->addData<StockData>("AAPL", 150.0, 0.2);
        marketData->addData<InterestRateData>("LIBOR", 0.05);

        double K = 100.0;
        auto payoff_call = std::make_unique<PayoffCall>(K);
        Option call(std::move(payoff_call), marketData, 1.0);

        auto payoff_put = std::make_unique<PayoffPut>(K);
        Option put(std::move(payoff_put), marketData, 1.0);
};

TEST_F(OptionTest, MovingSemantics) {
    // Action: Move call into option3, then move option3 into option2

    Option call_mov_1 = std::move(call); // Using the moving constructor
    option2 = std::move(option3); // Using the moving assignment operator

    // Verify: Check that option1 and option3 are "empty", and option2 has successfully
    // acquired the resources originally belonging to option1.
    EXPECT_EQ(call.getPayoff().get(), nullptr);
    EXPECT_NE(option2.getPayoff().get(), nullptr);
    EXPECT_EQ(option3.getPayoff().get(), nullptr);


}

/* Tests the copy semantics of the Option class, assuming the class supports copy operations.
   This test verifies that copying an Option object results in a new object with the same
   attributes but does not affect the original object's state upon modification. */
TEST_F(OptionTest, CopySemantics) {
    // Setup: Create an Option object with a PayoffCall.
    double K1 = 100.0;
    auto payoff_call1 = std::make_unique<PayoffCall>(K1);
    auto payoff_call2 = std::make_unique<PayoffCall>(K1);

    Option option1(std::move(payoff_call1), 0.05, 1.0, 150.0, 0.2);
    Option option2(std::move(payoff_call2), 0.05, 1.0, 150.0, 0.2);

    // Perform a copy operation to create option2 and option3 from option1
    Option option3(option1); // Using copy constructor
    option2 = option1; // Using copy assignment operator

    // Check if the attributes have been correctly copied using guetters
    EXPECT_EQ(option1.get_T(), option3.get_T()); // For copy constructor

    EXPECT_EQ(option1.get_T(), option2.get_T()); // For copy assignment operator

    //Using overloaded == operator
    EXPECT_TRUE(option1 == option2);
    EXPECT_TRUE(option1 == option3);

    // Modify option1 to see if it affects both option2 and option3
    double K2 = 50.0;
    auto payoff_change = std::make_unique<PayoffCall>(K2);
    option1 = Option(std::move(payoff_change), 0.10, 2.0, 100.0, 0.3);

    // Check that option2's and option3's payoff is not affected by changes to option1
    EXPECT_NE(option2.getPayoff().get(), nullptr);
    EXPECT_NE(option3.getPayoff().get(), nullptr);

    EXPECT_EQ(option2.get_T(), 1.0); // Original maturity before option1 was changed
    EXPECT_EQ(option3.get_T(), 1.0);
    EXPECT_EQ(option1.get_T(), 2.0);

    // Using overloaded != operator
    EXPECT_TRUE(option1 != option2);
    EXPECT_TRUE(option1 != option3);
}



