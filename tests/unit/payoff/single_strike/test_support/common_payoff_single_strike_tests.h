#ifndef COMMON_PAYOFF_SINGLE_STRIKE_TESTS_H
#define COMMON_PAYOFF_SINGLE_STRIKE_TESTS_H

#include <gtest/gtest.h>

template <typename T>
void testPayoffConstructor(double K) {
    EXPECT_NO_THROW(T payoff(K));
    EXPECT_THROW(T payoff(-K), std::invalid_argument);
}

template <typename T>
void testPayoffClone(double K) {
    T payoff(K);
    auto clone = payoff.clone();
    EXPECT_EQ(dynamic_cast<T&>(*clone), payoff);
    EXPECT_NE(clone.get(), &payoff);
}

template <typename T>
void testPayoffEquality(double K) {
    T payoff(K);
    T payoff2(K);
    T payoff3(K + 10.0);

    EXPECT_TRUE(payoff == payoff2);
    EXPECT_FALSE(payoff != payoff2);

    EXPECT_FALSE(payoff == payoff3);
    EXPECT_TRUE(payoff != payoff3);
}

template <typename T>
void testPayoffCalculation(double K, double expectedBelowK, double expectedAboveK) {
    T payoff(K);
    EXPECT_DOUBLE_EQ(payoff(90.0), expectedBelowK);
    EXPECT_DOUBLE_EQ(payoff(110.0), expectedAboveK);

    auto clone = payoff.clone();
    EXPECT_DOUBLE_EQ((*clone)(90.0), expectedBelowK);
    EXPECT_DOUBLE_EQ((*clone)(110.0), expectedAboveK);
}

#endif //COMMON_PAYOFF_SINGLE_STRIKE_TESTS_H
