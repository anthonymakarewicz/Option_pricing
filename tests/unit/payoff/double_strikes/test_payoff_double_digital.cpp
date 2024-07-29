#include "payoff/double_strikes/payoff_double_digital.h"
#include <gtest/gtest.h>

using namespace OptionPricer;

// Test fixture for PayoffDoubleDigital classes
class PayoffDoubleDigitalTest : public ::testing::Test {
protected:
    PayoffDoubleDigitalTest() : K_L(0.0), K_U(0.0) {}

    void SetUp() override {
        K_L = 90.0;
        K_U = 110.0;
    }

    double K_L;
    double K_U;
};

TEST_F(PayoffDoubleDigitalTest, PayoffDoubleDigitalConstructorTests) {
    EXPECT_NO_THROW(PayoffDoubleDigital pdd(K_L, K_U));
    EXPECT_THROW(PayoffDoubleDigital pdd(-K_L, K_U), std::invalid_argument);
    EXPECT_THROW(PayoffDoubleDigital pdd(K_L, -K_U), std::invalid_argument);
}

TEST_F(PayoffDoubleDigitalTest, PayoffDoubleDigitalCloneTests) {
    PayoffDoubleDigital pdd(K_L, K_U);
    auto clone = pdd.clone();

    EXPECT_EQ(dynamic_cast<PayoffDoubleDigital&>(*clone), pdd);
    EXPECT_NE(clone.get(), &pdd);
}

TEST_F(PayoffDoubleDigitalTest, PayoffDoubleDigitalEqualityTests) {
    PayoffDoubleDigital pdd(K_L, K_U);
    PayoffDoubleDigital pdd2(K_L, K_U);
    PayoffDoubleDigital pdd3(K_L, K_U + 10.0);

    EXPECT_TRUE(pdd == pdd2);
    EXPECT_FALSE(pdd != pdd2);
    EXPECT_FALSE(pdd == pdd3);
    EXPECT_TRUE(pdd != pdd3);
}

TEST_F(PayoffDoubleDigitalTest, PayoffDoubleDigitalPayoffCalculationTests) {
    PayoffDoubleDigital pdd(K_L, K_U);
    EXPECT_DOUBLE_EQ(pdd(85.0), 0.0);
    EXPECT_DOUBLE_EQ(pdd(95.0), 1.0);
    EXPECT_DOUBLE_EQ(pdd(115.0), 0.0);

    auto clone = pdd.clone();
    EXPECT_DOUBLE_EQ((*clone)(85.0), 0.0);
    EXPECT_DOUBLE_EQ((*clone)(95.0), 1.0);
    EXPECT_DOUBLE_EQ((*clone)(115.0), 0.0);
}