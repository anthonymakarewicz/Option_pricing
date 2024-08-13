#include "test_support/fixture_payoff_single_strike.h"
#include "payoff/single_strike/payoff_digital.h"

using namespace OptionPricer;

TEST_F(PayoffSingleStrikeTest, PayoffDigitalCallConstructorTests) {
    EXPECT_NO_THROW(PayoffDigital pdc(PayoffType::Call, K));
    EXPECT_THROW(PayoffDigital pdc(PayoffType::Call, -K), std::invalid_argument);
    EXPECT_THROW(PayoffDigital pdc(PayoffType::DoubleDigital, K), std::invalid_argument);
}

TEST_F(PayoffSingleStrikeTest, PayoffDigitalCallCloneTests) {
    const PayoffDigital pdc(PayoffType::Call, K);
    const auto clone = pdc.clone();

    // Check if the original and cloned objects are the same
    EXPECT_EQ(dynamic_cast<PayoffDigital&>(*clone), pdc);
    // Check if clone has its own memory location
    EXPECT_NE(clone.get(), &pdc);
}

TEST_F(PayoffSingleStrikeTest, PayoffDigitalCallEqualityTests) {
    const PayoffDigital pdc(PayoffType::Call, K);
    const PayoffDigital pdc2(PayoffType::Call, K);
    const PayoffDigital pdc3(PayoffType::Call, K + 10.0);

    EXPECT_TRUE(pdc == pdc2);
    EXPECT_FALSE(pdc != pdc2);
    EXPECT_FALSE(pdc == pdc3);
    EXPECT_TRUE(pdc != pdc3);
}

TEST_F(PayoffSingleStrikeTest, PayoffDigitalCallCalculationTests) {
    const PayoffDigital pdc(PayoffType::Call, K); // 100
    EXPECT_DOUBLE_EQ(pdc(90.0), 0.0);
    EXPECT_DOUBLE_EQ(pdc(110.0), 1.0);

    const PayoffDigital pdc2(PayoffType::Call, K + 5.0); // K = 105
    EXPECT_DOUBLE_EQ(pdc2(90.0), 0.0);
    EXPECT_DOUBLE_EQ(pdc2(110.0), 1.0);

    const auto clone = pdc.clone();
    EXPECT_DOUBLE_EQ((*clone)(90.0), 0.0);
    EXPECT_DOUBLE_EQ((*clone)(110.0), 1.0);
}


TEST_F(PayoffSingleStrikeTest, PayoffDigitalPutConstructorTests) {
    EXPECT_NO_THROW(PayoffDigital pdp(PayoffType::Call, K));
    EXPECT_THROW(PayoffDigital pdp(PayoffType::Call, -K), std::invalid_argument);
    EXPECT_THROW(PayoffDigital pdp(PayoffType::DoubleDigital, K), std::invalid_argument);
}

TEST_F(PayoffSingleStrikeTest, PayoffDigitalPutCloneTests) {
    const PayoffDigital pdp(PayoffType::Put, K);
    const auto clone = pdp.clone();

    // Check if the original and cloned objects are the same
    EXPECT_EQ(dynamic_cast<PayoffDigital&>(*clone), pdp);
    // Check if clone has its own memory location
    EXPECT_NE(clone.get(), &pdp);
}

TEST_F(PayoffSingleStrikeTest, PayoffDigitalPutEqualityTests) {
    const PayoffDigital pdp(PayoffType::Put, K);
    const PayoffDigital pdp2(PayoffType::Put, K);
    const PayoffDigital pdp3(PayoffType::Put, K + 10.0);

    EXPECT_TRUE(pdp == pdp2);
    EXPECT_FALSE(pdp != pdp2);
    EXPECT_FALSE(pdp == pdp3);
    EXPECT_TRUE(pdp != pdp3);
}

TEST_F(PayoffSingleStrikeTest, PayoffDigitalPutCalculationTests) {
    const PayoffDigital pdp(PayoffType::Put, K); // 100
    EXPECT_DOUBLE_EQ(pdp(90.0), 1.0);
    EXPECT_DOUBLE_EQ(pdp(110.0), 0.0);

    const PayoffDigital pdp2(PayoffType::Put, K + 5.0); // K = 105
    EXPECT_DOUBLE_EQ(pdp2(90.0), 1.0);
    EXPECT_DOUBLE_EQ(pdp2(110.0), 0.0);

    const auto clone = pdp.clone();
    EXPECT_DOUBLE_EQ((*clone)(90.0), 1.0);
    EXPECT_DOUBLE_EQ((*clone)(110.0), 0.0);
}