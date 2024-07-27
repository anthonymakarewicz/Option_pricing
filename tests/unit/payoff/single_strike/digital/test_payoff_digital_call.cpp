#include "../test_support/fixture_payoff_single_strike.h"
#include "payoff/single_strike/digital/payoff_digital_call.h"

TEST_F(PayoffSingleStrikeTest, PayoffDigitalCallConstructorTests) {
    EXPECT_NO_THROW(PayoffDigitalCall pdc(K));
    EXPECT_THROW(PayoffDigitalCall pdc(-K), std::invalid_argument);
}

TEST_F(PayoffSingleStrikeTest, PayoffDigitalCallCloneTests) {
    PayoffDigitalCall pdc(K);
    auto clone = pdc.clone();

    // Check if the original and cloned objects are the same
    EXPECT_EQ(dynamic_cast<PayoffDigitalCall&>(*clone), pdc);
    // Check if clone has its own memory location
    EXPECT_NE(clone.get(), &pdc);
}

TEST_F(PayoffSingleStrikeTest, PayoffDigitalCallEqualityTests) {
    PayoffDigitalCall pdc(K);
    PayoffDigitalCall pdc2(K);
    PayoffDigitalCall pdc3(K + 10.0);

    EXPECT_TRUE(pdc == pdc2);
    EXPECT_FALSE(pdc != pdc2);
    EXPECT_FALSE(pdc == pdc3);
    EXPECT_TRUE(pdc != pdc3);

}

TEST_F(PayoffSingleStrikeTest, PayoffDigitalCallCalculationTests) {
    PayoffDigitalCall pdc(K); // K = 100
    EXPECT_DOUBLE_EQ(pdc(90.0), 0.0);
    EXPECT_DOUBLE_EQ(pdc(110.0), 1.0);

    PayoffDigitalCall pdc2(K + 5.0); // K = 105
    EXPECT_DOUBLE_EQ(pdc2(90.0), 0.0);
    EXPECT_DOUBLE_EQ(pdc2(110.0), 1.0);

    auto clone = pdc.clone();
    EXPECT_DOUBLE_EQ((*clone)(90.0), 0.0);
    EXPECT_DOUBLE_EQ((*clone)(110.0), 1.0);
}
