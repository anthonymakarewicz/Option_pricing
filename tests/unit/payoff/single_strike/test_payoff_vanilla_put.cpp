#include "test_support/fixture_payoff_single_strike.h"
#include "payoff/single_strike/payoff_vanilla_put.h"

TEST_F(PayoffSingleStrikeTest, PayoffVanillaPutConstructorTests) {
    EXPECT_NO_THROW(PayoffVanillaPut pvc(K));
    EXPECT_THROW(PayoffVanillaPut pvc(-K), std::invalid_argument);
}

TEST_F(PayoffSingleStrikeTest, PayoffVanillaPutCloneTests) {
    PayoffVanillaPut pvp(K);
    auto clone = pvp.clone();

    // Check if the original and cloned objects are the same
    EXPECT_EQ(dynamic_cast<PayoffVanillaPut&>(*clone), pvp);
    // Check if clone has its own memory location
    EXPECT_NE(clone.get(), &pvp);
}

TEST_F(PayoffSingleStrikeTest, PayoffVanillaPutEqualityTests) {
    PayoffVanillaPut pvp(K);
    PayoffVanillaPut pvp2(K);
    PayoffVanillaPut pvp3(K + 10.0);

    EXPECT_TRUE(pvp == pvp2);
    EXPECT_FALSE(pvp != pvp2);
    EXPECT_FALSE(pvp == pvp3);
    EXPECT_TRUE(pvp != pvp3);
}

TEST_F(PayoffSingleStrikeTest, PayoffVanillaPutPayoffCalculationTests) {
    PayoffVanillaPut pvp(K); // K = 100
    EXPECT_DOUBLE_EQ(pvp(90.0), 10.0);
    EXPECT_DOUBLE_EQ(pvp(110.0), 0.0);

    auto clone = pvp.clone();
    EXPECT_DOUBLE_EQ((*clone)(90.0), 10.0);
    EXPECT_DOUBLE_EQ((*clone)(110.0), 0.0);
}