#include "test_support/fixture_payoff_single_strike.h"
#include "payoff/single_strike/payoff_vanilla.h"

using namespace OptionPricer;

TEST_F(PayoffSingleStrikeTest, PayoffVanillaCallConstructorTests) {
    EXPECT_NO_THROW(PayoffVanilla pvc(PayoffType::Call, K));
    EXPECT_THROW(PayoffVanilla pvc(PayoffType::Call, -K), std::invalid_argument);
    EXPECT_THROW(PayoffVanilla pvc(PayoffType::DoubleDigital, K), std::invalid_argument);
}

TEST_F(PayoffSingleStrikeTest, PayoffVanillaCallCloneTests) {
    PayoffVanilla pvc(PayoffType::Call, K);
    const auto clone = pvc.clone();

    // Check if the original and cloned objects are the same
    EXPECT_EQ(dynamic_cast<PayoffVanilla&>(*clone), pvc);
    // Check if clone has its own memory location
    EXPECT_NE(clone.get(), &pvc);
}

TEST_F(PayoffSingleStrikeTest, PayoffVanillaCallEqualityTests) {
    const PayoffVanilla pvc(PayoffType::Call, K);
    const PayoffVanilla pvc2(PayoffType::Call, K);
    const PayoffVanilla pvc3(PayoffType::Call, K + 10.0);

    EXPECT_TRUE(pvc == pvc2);
    EXPECT_FALSE(pvc != pvc2);
    EXPECT_FALSE(pvc == pvc3);
    EXPECT_TRUE(pvc != pvc3);
}

TEST_F(PayoffSingleStrikeTest, PayoffVanillaCallPayoffCalculationTests) {
    const PayoffVanilla pvc(PayoffType::Call, K);
    EXPECT_DOUBLE_EQ(pvc(90.0), 0.0);
    EXPECT_DOUBLE_EQ(pvc(110.0), 10.0);

    const auto clone = pvc.clone();
    EXPECT_DOUBLE_EQ((*clone)(90.0), 0.0);
    EXPECT_DOUBLE_EQ((*clone)(110.0), 10.0);
}


TEST_F(PayoffSingleStrikeTest, PayoffVanillaPutConstructorTests) {
    EXPECT_NO_THROW(PayoffVanilla pvc(PayoffType::Put, K));
    EXPECT_THROW(PayoffVanilla pvc(PayoffType::Put, -K), std::invalid_argument);
    EXPECT_THROW(PayoffVanilla pvc(PayoffType::DoubleDigital, K), std::invalid_argument);
}

TEST_F(PayoffSingleStrikeTest, PayoffVanillaPutCloneTests) {
    const PayoffVanilla pvp(PayoffType::Put, K);
    const auto clone = pvp.clone();

    // Check if the original and cloned objects are the same
    EXPECT_EQ(dynamic_cast<PayoffVanilla&>(*clone), pvp);
    // Check if clone has its own memory location
    EXPECT_NE(clone.get(), &pvp);
}

TEST_F(PayoffSingleStrikeTest, PayoffVanillaPutEqualityTests) {
    const PayoffVanilla pvp(PayoffType::Put, K);
    const PayoffVanilla pvp2(PayoffType::Put, K);
    const PayoffVanilla pvp3(PayoffType::Put, K + 10.0);

    EXPECT_TRUE(pvp == pvp2);
    EXPECT_FALSE(pvp != pvp2);
    EXPECT_FALSE(pvp == pvp3);
    EXPECT_TRUE(pvp != pvp3);
}

TEST_F(PayoffSingleStrikeTest, PayoffVanillaPutPayoffCalculationTests) {
    const PayoffVanilla pvp(PayoffType::Put, K); // K = 100
    EXPECT_DOUBLE_EQ(pvp(90.0), 10.0);
    EXPECT_DOUBLE_EQ(pvp(110.0), 0.0);

    const auto clone = pvp.clone();
    EXPECT_DOUBLE_EQ((*clone)(90.0), 10.0);
    EXPECT_DOUBLE_EQ((*clone)(110.0), 0.0);
}
