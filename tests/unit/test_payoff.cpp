#ifndef TEST_PAYOFF_CPP
#define TEST_PAYOFF_CPP

#include <iostream>
#include <gtest/gtest.h>
#include "payoff.h"

// Test fixture for PayoffSingleStrike classes
class PayoffSingleStrikeTest : public ::testing::Test {
protected:
    void SetUp() override {
        K = 100.0;
    }

    double K;
};

// Test fixture for PayoffDoubleStrikes classes
class PayoffDoubleStrikesTest : public ::testing::Test {
protected:
    void SetUp() override {
        K_L = 90.0;
        K_U = 110.0;
    }

    double K_L;
    double K_U;
};

// Test PayoffCall
TEST_F(PayoffSingleStrikeTest, PayoffCallTests) {
    EXPECT_NO_THROW(PayoffCall pc(K));
    EXPECT_THROW(PayoffCall pc(-K), std::invalid_argument);

    PayoffCall pc(K);
    auto clone = pc.clone();
    EXPECT_DOUBLE_EQ(dynamic_cast<PayoffSingleStrike*>(clone.get())->getK(), K);

    EXPECT_DOUBLE_EQ(pc(90.0), 0.0);
    EXPECT_DOUBLE_EQ(pc(110.0), 10.0);
    EXPECT_DOUBLE_EQ((*clone)(90.0), 0.0);
    EXPECT_DOUBLE_EQ((*clone)(110.0), 10.0);
}

// Test PayoffPut
TEST_F(PayoffSingleStrikeTest, PayoffPutTests) {
    EXPECT_NO_THROW(PayoffPut pp(K));
    EXPECT_THROW(PayoffPut pp(-K), std::invalid_argument);

    PayoffPut pp(K);
    auto clone = pp.clone();
    EXPECT_DOUBLE_EQ(dynamic_cast<PayoffSingleStrike*>(clone.get())->getK(), K);

    EXPECT_DOUBLE_EQ(pp(90.0), 10.0);
    EXPECT_DOUBLE_EQ(pp(110.0), 0.0);
    EXPECT_DOUBLE_EQ((*clone)(90.0), 10.0);
    EXPECT_DOUBLE_EQ((*clone)(110.0), 0.0);
}

// Test PayoffDigitalCall
TEST_F(PayoffSingleStrikeTest, PayoffDigitalCallTests) {
    EXPECT_NO_THROW(PayoffDigitalCall pdc(K));
    EXPECT_THROW(PayoffDigitalCall pdc(-K), std::invalid_argument);

    PayoffDigitalCall pdc(K);
    auto clone = pdc.clone();
    EXPECT_DOUBLE_EQ(dynamic_cast<PayoffSingleStrike*>(clone.get())->getK(), K);

    EXPECT_DOUBLE_EQ(pdc(90.0), 0.0);
    EXPECT_DOUBLE_EQ(pdc(110.0), 1.0);
    EXPECT_DOUBLE_EQ((*clone)(90.0), 0.0);
    EXPECT_DOUBLE_EQ((*clone)(110.0), 1.0);
}

// Test PayoffDigitalPut
TEST_F(PayoffSingleStrikeTest, PayoffDigitalPutTests) {
    EXPECT_NO_THROW(PayoffDigitalPut pdp(K));
    EXPECT_THROW(PayoffDigitalPut pdp(-K), std::invalid_argument);

    PayoffDigitalPut pdp(K);
    auto clone = pdp.clone();
    EXPECT_DOUBLE_EQ(dynamic_cast<PayoffSingleStrike*>(clone.get())->getK(), K);

    EXPECT_DOUBLE_EQ(pdp(90.0), 1.0);
    EXPECT_DOUBLE_EQ(pdp(110.0), 0.0);
    EXPECT_DOUBLE_EQ((*clone)(90.0), 1.0);
    EXPECT_DOUBLE_EQ((*clone)(110.0), 0.0);
}

// Test PayoffDoubleDigital
TEST_F(PayoffDoubleStrikesTest, PayoffDoubleDigitalTests) {
    EXPECT_NO_THROW(PayoffDoubleDigital pdd(K_L, K_U));
    EXPECT_THROW(PayoffDoubleDigital pdd(-K_L, K_U), std::invalid_argument);
    EXPECT_THROW(PayoffDoubleDigital pdd(K_L, -K_U), std::invalid_argument);

    PayoffDoubleDigital pdd(K_L, K_U);
    auto clone = pdd.clone();
    EXPECT_DOUBLE_EQ(dynamic_cast<PayoffDoubleStrikes*>(clone.get())->getKL(), K_L);
    EXPECT_DOUBLE_EQ(dynamic_cast<PayoffDoubleStrikes*>(clone.get())->getKU(), K_U);

    EXPECT_DOUBLE_EQ(pdd(85.0), 0.0);
    EXPECT_DOUBLE_EQ(pdd(95.0), 1.0);
    EXPECT_DOUBLE_EQ(pdd(115.0), 0.0);
    EXPECT_DOUBLE_EQ((*clone)(85.0), 0.0);
    EXPECT_DOUBLE_EQ((*clone)(95.0), 1.0);
    EXPECT_DOUBLE_EQ((*clone)(115.0), 0.0);
}

#endif //TEST_PAYOFF_CPP