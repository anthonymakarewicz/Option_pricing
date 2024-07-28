#include "test_support/fixture_payoff_single_strike.h"
#include "payoff/single_strike/payoff_digital_put.h"

TEST_F(PayoffSingleStrikeTest, PayoffDigitalPutConstructorTests) {
    EXPECT_NO_THROW(PayoffDigitalPut pdp(K));
    EXPECT_THROW(PayoffDigitalPut pdp(-K), std::invalid_argument);
}

TEST_F(PayoffSingleStrikeTest, PayoffDigitalPutCloneTests) {
    PayoffDigitalPut pdp(K);
    auto clone = pdp.clone();

    // Check if the original and cloned objects are the same
    EXPECT_EQ(dynamic_cast<PayoffDigitalPut&>(*clone), pdp);
    // Check if clone has its own memory location
    EXPECT_NE(clone.get(), &pdp);
}

TEST_F(PayoffSingleStrikeTest, PayoffDigitalPutEqualityTests) {
    PayoffDigitalPut pdp(K);
    PayoffDigitalPut pdp2(K);
    PayoffDigitalPut pdp3(K + 10.0);

    EXPECT_TRUE(pdp == pdp2);
    EXPECT_FALSE(pdp != pdp2);
    EXPECT_FALSE(pdp == pdp3);
    EXPECT_TRUE(pdp != pdp3);
}

TEST_F(PayoffSingleStrikeTest, PayoffDigitalPutCalculationTests) {
    PayoffDigitalPut pdp(K); // K = 100
    EXPECT_DOUBLE_EQ(pdp(90.0), 1.0);
    EXPECT_DOUBLE_EQ(pdp(110.0), 0.0);

    PayoffDigitalPut pdp2(K + 5.0); // K = 105
    EXPECT_DOUBLE_EQ(pdp2(90.0), 1.0);
    EXPECT_DOUBLE_EQ(pdp2(110.0), 0.0);

    auto clone = pdp.clone();
    EXPECT_DOUBLE_EQ((*clone)(90.0), 1.0);
    EXPECT_DOUBLE_EQ((*clone)(110.0), 0.0);
}
