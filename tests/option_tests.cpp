
// Test Suite for Option Class

#include <gtest/gtest.h>

#include "payoff.h"
#include "market_data.h"
#include "option.h"

/*Only test for PayoffCall as we have already tested the PayoffPut
 * functionaility ointo the payoff_tests.cpp
 */
class OptionTest: public::testing::Test {
protected:
    double K;
    double T;

    std::shared_ptr<MarketData> mdata;
    std::shared_ptr<StockData> stock_data;
    std::shared_ptr<InterestRateData> ir_data;
    std::unique_ptr<PayoffCall> payoff_call_1;
    std::unique_ptr<PayoffCall> payoff_call_2;

    void SetUp() override {
        K = 100.0;
        T = 1.0;

        mdata = std::make_shared<MarketData>();
        mdata->addData<StockData>("AAPL", 150.0, 0.2);
        mdata->addData<InterestRateData>("LIBOR", 0.05);
        stock_data = mdata->getData<StockData>("AAPL");
        ir_data = mdata->getData<InterestRateData>("LIBOR");

        payoff_call_1 = std::make_unique<PayoffCall>(K);
        payoff_call_2 = std::make_unique<PayoffCall>(K);
    }
};


TEST_F(OptionTest, MovingSemantics) {
    auto call_1 = Option(std::move(payoff_call_1), stock_data, ir_data, T);
    auto call_2 = Option(std::move(payoff_call_2), stock_data, ir_data, T);

    Option call_3 = std::move(call_1); // Using the moving constructor
    call_2 = std::move(call_3); // Using the moving assignment operator

    // Verify: Check that option1 and option3 are "empty", and option2 has successfully
    // acquired the resources originally belonging to option1.
    EXPECT_EQ(call_1.getPayoff().get(), nullptr);
    EXPECT_NE(call_2.getPayoff().get(), nullptr);
    EXPECT_EQ(call_3.getPayoff().get(), nullptr);
}


TEST_F(OptionTest, CopySemantics) {
    auto call_1 = Option(std::move(payoff_call_1), stock_data, ir_data, T);
    auto call_2 = Option(std::move(payoff_call_2), stock_data, ir_data, T);

    // Perform a copy operation to create call_2 and call_3 from call_1
    Option call_3(call_1); // Using copy constructor
    call_2 = call_1; // Using copy assignment operator

    // Check if the attributes have been correctly copied using guetters
    EXPECT_EQ(call_1.get_T(), call_3.get_T()); // For copy constructor
    EXPECT_EQ(call_1.get_S(), call_3.get_S());
    EXPECT_EQ(call_1.get_sigma(), call_3.get_sigma());
    EXPECT_EQ(call_1.get_r(), call_3.get_r());

    EXPECT_EQ(call_1.get_T(), call_2.get_T()); // For copy assignment operator
    EXPECT_EQ(call_1.get_S(), call_2.get_S());
    EXPECT_EQ(call_1.get_sigma(), call_2.get_sigma());
    EXPECT_EQ(call_1.get_r(), call_2.get_r());

    //Using overloaded == operator
    EXPECT_TRUE(call_1 == call_2);
    EXPECT_TRUE(call_1 == call_3);

    // Modify call_1 to see if it affects both call_2 and call_3
    double K2 = 50.0;
    double T2 = 0.5;
    auto new_payoff = std::make_unique<PayoffCall>(K2);

    call_1 = Option(std::move(new_payoff), stock_data, ir_data, T2);

    // Check that call_2's and call_3's payoff is not affected by changes to call_1
    EXPECT_NE(call_2.getPayoff().get(), nullptr);
    EXPECT_NE(call_3.getPayoff().get(), nullptr);

    EXPECT_EQ(call_2.get_T(), 1.0); // Original maturity before call_1 was changed
    EXPECT_EQ(call_3.get_T(), 1.0);
    EXPECT_EQ(call_1.get_T(), 0.5); // New maturity for call_1

    // Using overloaded != operator
    EXPECT_TRUE(call_1 != call_2);
    EXPECT_TRUE(call_1 != call_3);
}

