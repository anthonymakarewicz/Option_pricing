#ifndef FIXTURE_PAYOFF_SINGLE_STRIKE_H
#define FIXTURE_PAYOFF_SINGLE_STRIKE_H

#include <gtest/gtest.h>

class PayoffSingleStrikeTest : public ::testing::Test {
protected:
    PayoffSingleStrikeTest() : K(0.0) {}

    void SetUp() override {
        K = 100.0;
    }
    double K;
};

#endif //FIXTURE_PAYOFF_SINGLE_STRIKE_H
