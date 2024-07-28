#include "test_support/fixture_payoff_single_strike.h"
#include "payoff/single_strike/payoff_vanilla_call.h"

TEST_F(PayoffSingleStrikeTest, PayoffVanillaCallConstructorTests) {
    EXPECT_NO_THROW(PayoffVanillaCall pvc(K));
    EXPECT_THROW(PayoffVanillaCall pvc(-K), std::invalid_argument);
}

TEST_F(PayoffSingleStrikeTest, PayoffVanillaCallCloneTests) {
    PayoffVanillaCall pvc(K);
    auto clone = pvc.clone();

    // Check if the original and cloned objects are the same
    EXPECT_EQ(dynamic_cast<PayoffVanillaCall&>(*clone), pvc);
    // Check if clone has its own memory location
    EXPECT_NE(clone.get(), &pvc);
}

TEST_F(PayoffSingleStrikeTest, PayoffVanillaCallEqualityTests) {
    PayoffVanillaCall pvc(K);
    PayoffVanillaCall pvc2(K);
    PayoffVanillaCall pvc3(K + 10.0);

    EXPECT_TRUE(pvc == pvc2);
    EXPECT_FALSE(pvc != pvc2);
    EXPECT_FALSE(pvc == pvc3);
    EXPECT_TRUE(pvc != pvc3);
}

TEST_F(PayoffSingleStrikeTest, PayoffVanillaCallPayoffCalculationTests) {
    PayoffVanillaCall pvc(K);
    EXPECT_DOUBLE_EQ(pvc(90.0), 0.0);
    EXPECT_DOUBLE_EQ(pvc(110.0), 10.0);

    auto clone = pvc.clone();
    EXPECT_DOUBLE_EQ((*clone)(90.0), 0.0);
    EXPECT_DOUBLE_EQ((*clone)(110.0), 10.0);
}
