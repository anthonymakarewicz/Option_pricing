
#include <iostream>
#include "payoff.h"

#include <gtest/gtest.h>

/* To run only one particular test case, e.g. StandardPayoff follow these instructions:
 * - Go to the cmake directory where the Option_tester binary is located
 * if located in the project directory Option_pricer the path is:
 * --> cd cmake-build-cmake/tests
 * - Enter  ./Option_tester --gtest_filter=PayoffTest.StandardPayoff in the console
 */
TEST(PayoffTest, StandardPayoff) {
    // Vanilla Call and Put payoffs
    double K = 150.0;
    PayoffCall payoff_call(K);
    PayoffPut payoff_put(K);

    // Call payoff: max(S - K, 0)
    EXPECT_EQ(payoff_call(250.0), 100.0); // Call option in-the-money
    EXPECT_EQ(payoff_call(50.0), 0.0); // Call option out-of-the-money

    // Put payoff: max(K - S, 0)
    EXPECT_EQ(payoff_put(250.0), 0.0); // Put option out-of-the-money
    EXPECT_EQ(payoff_put(50.0), 100.0); // Put option in-the-money

    // Polymorphism
    auto ptr_payoff_call = std::make_unique<PayoffCall>(K);
    auto ptr_payoff_put = std::make_unique<PayoffPut>(K);

    // Using the base class pointer to call the derived class's overridden operator()
    EXPECT_EQ((*ptr_payoff_call)(250.0), 100.0); // Call option, in-the-money
    EXPECT_EQ((*ptr_payoff_call)(50.0), 0.0); // Call option, out-of-the-money

    EXPECT_EQ((*ptr_payoff_put)(250.0), 0.0); // Put option, in-the-money
    EXPECT_EQ((*ptr_payoff_put)(50.0), 100.0); // Put option, out-of-the-money

    // Clone the option to a unique_ptr<Payoff>
    auto ptr_payoff_call_clone = ptr_payoff_call->clone();
    auto ptr_payoff_put_clone = ptr_payoff_put->clone();

    // Check that the cloned and original objects have the same state
    EXPECT_EQ((*ptr_payoff_call_clone)(250.0), (*ptr_payoff_call)(250.0));
    EXPECT_EQ((*ptr_payoff_put_clone)(50.0), (*ptr_payoff_put)(50.0));
}

TEST(PayoffTest, PayoffDigital) {
    // Digital Call and Put payoffs
    double K = 150.0;
    PayoffDigitalCall payoff_digit_call(K);
    PayoffDigitalPut payoff_digit_put(K);

    // Call payoff: max(I(S - K), 0)
    EXPECT_EQ(payoff_digit_call(250.0), 1.0); // Call option in-the-money
    EXPECT_EQ(payoff_digit_call(90.0), 0.0); // Call option out-of-the-money

    // Put payoff: max(I(K - S), 0)
    EXPECT_EQ(payoff_digit_put(250.0), 0.0); // Put option out-of-the-money
    EXPECT_EQ(payoff_digit_put(90.0), 1.0); // Put option in-the-money

    // Polymorphism
    auto ptr_payoff_digit_call = std::make_unique<PayoffDigitalCall>(K);
    auto ptr_payoff_digit_put = std::make_unique<PayoffDigitalPut>(K);

    // Using the base class pointer to call the derived class's overridden operator()
    EXPECT_EQ((*ptr_payoff_digit_call)(250.0), 1.0); // Call option, in-the-money
    EXPECT_EQ((*ptr_payoff_digit_call)(90.0), 0.0); // Call option, out-of-the-money

    EXPECT_EQ((*ptr_payoff_digit_put)(250.0), 0.0); // Put option, in-the-money
    EXPECT_EQ((*ptr_payoff_digit_put)(90.0), 1.0); // Put option, out-of-the-money

    // Cloning
    auto ptr_payoff_digit_call_clone = ptr_payoff_digit_call->clone();
    auto ptr_payoff_put_digit_clone = ptr_payoff_digit_put->clone();

    // Check that the cloned and original objects have the same state
    EXPECT_EQ((*ptr_payoff_digit_call_clone)(250.0), (*ptr_payoff_digit_call)(250.0));
    EXPECT_EQ((*ptr_payoff_put_digit_clone)(90.0), (*ptr_payoff_digit_put)(90.0));
}

TEST(PayoffTest, PayoffDoubleDigital) {
    // Double Digital payoff
    double K_L = 70.0;
    double K_U = 100.0;
    PayoffDoubleDigital payoff_dbl_digit(K_L, K_U);

    // Double Digital payoff: max(I(K_L <= S <= K_U), 0)
    EXPECT_EQ(payoff_dbl_digit(50.0), 0.0); // Out-of-the-money Low
    EXPECT_EQ(payoff_dbl_digit(80.0), 1.0); // In-the-money
    EXPECT_EQ(payoff_dbl_digit(150.0), 0.0); // Out-of-the-money Up

    // Polymorphism
    auto ptr_payoff_dbl_digit = std::make_unique<PayoffDoubleDigital>(K_L, K_U);

    // Using the base class pointer to call the derived class's overridden operator()
    EXPECT_EQ((*ptr_payoff_dbl_digit)(50.0), 0.0); // Out-of-the-money Low
    EXPECT_EQ((*ptr_payoff_dbl_digit)(80.0), 1.0); // In-the-money
    EXPECT_EQ((*ptr_payoff_dbl_digit)(150.0), 0.0); // Out-of-the-money Up

    // Cloning
    auto ptr_payoff_dbl_digit_clone = ptr_payoff_dbl_digit->clone();

    // Check that the cloned and original objects have the same state
    EXPECT_EQ((*ptr_payoff_dbl_digit_clone)(50.0), (*ptr_payoff_dbl_digit)(50.0));
    EXPECT_EQ((*ptr_payoff_dbl_digit_clone)(80.0), (*ptr_payoff_dbl_digit)(80.0));
    EXPECT_EQ((*ptr_payoff_dbl_digit_clone)(150.0), (*ptr_payoff_dbl_digit)(150.0));
}

