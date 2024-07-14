
find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})

# Define the test executable
add_executable(Option_tester test_main.cpp test_market_data.cpp test_payoff.cpp
               ../src/payoff.cpp
               ../src/market_data.cpp)
               # ../src/option.cpp)

# Link Google Test to the test executable
target_link_libraries(Option_tester GTest::GTest GTest::Main)

# Optionally, register tests with CMake's testing system
add_test(NAME OptionTester COMMAND Option_tester)



