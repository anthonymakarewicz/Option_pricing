


find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})


# Define the test executable
add_executable(Option_tester option_tests.cpp payoff_tests.cpp market_data_tests.cpp
               ../src/option.cpp
               ../src/payoff.cpp
               ../src/market_data.cpp)

# Link Google Test to the test executable
target_link_libraries(Option_tester GTest::GTest GTest::Main)

# Optionally, register tests with CMake's testing system
add_test(NAME OptionTester COMMAND Option_tester)



