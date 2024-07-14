# Find Google Test
find_package(GTest REQUIRED)
#find_package(GMock REQUIRED)

# Define the test executable
add_executable(Option_tester
        test_main.cpp
        test_market_data.cpp
        test_payoff.cpp
        #test_option.cpp
        ../src/payoff.cpp
        ../src/market_data.cpp
        ../src/option.cpp)

# Link Google Test and Google Mock to the test executable
target_link_libraries(Option_tester GTest::GTest GTest::Main) #GMock::GMock)

# Optionally, register tests with CMake's testing system
add_test(NAME OptionTester COMMAND Option_tester)