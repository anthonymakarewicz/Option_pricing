
#include <iostream>
#include "payoff.h"

#include <gtest/gtest.h>



/* To run only one particular test case, e.g. StandardPayoff follow these instructions:
 * - Go to the cmake directory where the Option_tester binary is located
 * if located in the project directory Option_pricer the path is:
 * --> cd cmake-build-cmake/tests
 * - Enter  ./Option_tester --gtest_filter=PayoffTest.StandardPayoff in the console
 */
#include <gtest/gtest.h>
#include "payoff.h"

class PayoffSingleStrikeTest : public ::testing::Test {
protected:
    void SetUp() override {
        K = 100.0;
    }

    double K;
};

class PayoffDoubleStrikesTest : public ::testing::Test {
protected:
    void SetUp() override {
        lowerStrike = 90.0;
        upperStrike = 110.0;
    }

    double lowerStrike;
    double upperStrike;
};

// Tests for PayoffCall
TEST_F(PayoffSingleStrikeTest, PayoffCallTests) {
    // Construction
    EXPECT_NO_THROW(PayoffCall(strike));
    EXPECT_THROW(PayoffCall(-K), std::invalid_argument);

    // Clone
    PayoffCall pc(K);
    auto clone = pc.clone();
    EXPECT_DOUBLE_EQ(clone->getK(), K);

    // Operator()
    EXPECT_DOUBLE_EQ(pc(90.0), 0.0);
    EXPECT_DOUBLE_EQ(pc(110.0), 10.0);
    EXPECT_DOUBLE_EQ((*clone)(90.0), 0.0);
    EXPECT_DOUBLE_EQ((*clone)(110.0), 10.0);
}

// Tests for PayoffPut
TEST_F(PayoffSingleStrikeTest, PayoffPutTests) {
    // Construction
    EXPECT_NO_THROW(PayoffPut(K));
    EXPECT_THROW(PayoffPut(-K), std::invalid_argument);

    // Clone
    PayoffPut pp(K);
    auto clone = pp.clone();
    EXPECT_DOUBLE_EQ(clone->getK(), K);

    // Operator()
    EXPECT_DOUBLE_EQ(pp(90.0), 10.0);
    EXPECT_DOUBLE_EQ(pp(110.0), 0.0);
    EXPECT_DOUBLE_EQ((*clone)(90.0), 10.0);
    EXPECT_DOUBLE_EQ((*clone)(110.0), 0.0);
}

// Tests for PayoffDigitalCall
TEST_F(PayoffSingleStrikeTest, PayoffDigitalCallTests) {
    // Construction
    EXPECT_NO_THROW(PayoffDigitalCall(strike));
    EXPECT_THROW(PayoffDigitalCall(-K), std::invalid_argument);

    // Clone
    PayoffDigitalCall pdc(K);
    auto clone = pdc.clone();
    EXPECT_DOUBLE_EQ(clone->getK(), K);

    // Operator()
    EXPECT_DOUBLE_EQ(pdc(90.0), 0.0);
    EXPECT_DOUBLE_EQ(pdc(110.0), 1.0);
    EXPECT_DOUBLE_EQ((*clone)(90.0), 0.0);
    EXPECT_DOUBLE_EQ((*clone)(110.0), 1.0);
}

// Tests for PayoffDigitalPut
TEST_F(PayoffSingleStrikeTest, PayoffDigitalPutTests) {
    // Construction
    EXPECT_NO_THROW(PayoffDigitalPut(strike));
    EXPECT_THROW(PayoffDigitalPut(-K), std::invalid_argument);

    // Clone
    PayoffDigitalPut pdp(K);
    auto clone = pdp.clone();
    EXPECT_DOUBLE_EQ(clone->getK(), K);

    // Operator()
    EXPECT_DOUBLE_EQ(pdp(90.0), 1.0);
    EXPECT_DOUBLE_EQ(pdp(110.0), 0.0);
    EXPECT_DOUBLE_EQ((*clone)(90.0), 1.0);
    EXPECT_DOUBLE_EQ((*clone)(110.0), 0.0);
}

// Tests for PayoffDoubleDigital
TEST_F(PayoffDoubleStrikesTest, PayoffDoubleDigitalTests) {
    // Construction
    EXPECT_NO_THROW(PayoffDoubleDigital(lowerStrike, upperStrike));
    EXPECT_THROW(PayoffDoubleDigital(-lowerStrike, upperStrike), std::invalid_argument);
    EXPECT_THROW(PayoffDoubleDigital(lowerStrike, -upperStrike), std::invalid_argument);

    // Clone
    PayoffDoubleDigital pdd(lowerStrike, upperStrike);
    auto clone = pdd.clone();
    EXPECT_DOUBLE_EQ(clone->getKL(), lowerStrike);
    EXPECT_DOUBLE_EQ(clone->getKU(), upperStrike);

    // Operator()
    EXPECT_DOUBLE_EQ(pdd(85.0), 0.0);
    EXPECT_DOUBLE_EQ(pdd(95.0), 1.0);
    EXPECT_DOUBLE_EQ(pdd(115.0), 0.0);
    EXPECT_DOUBLE_EQ((*clone)(85.0), 0.0);
    EXPECT_DOUBLE_EQ((*clone)(95.0), 1.0);
    EXPECT_DOUBLE_EQ((*clone)(115.0), 0.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


