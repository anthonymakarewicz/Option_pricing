# Unit tests configuration
find_package(GTest REQUIRED)

# Create the executable called Unit_tests
add_executable(Unit_tests ${CMAKE_CURRENT_SOURCE_DIR}/../test_main.cpp
        option/test_base_option.cpp
        option/test_european_option.cpp
        option/test_factory_european_option.cpp
        market_data/test_stock_data.cpp
        market_data/test_market_data.cpp
        payoff/single_strike/test_payoff_vanilla_call.cpp
        payoff/single_strike/test_payoff_vanilla_put.cpp
        payoff/single_strike/test_payoff_digital_call.cpp
        payoff/single_strike/test_payoff_digital_put.cpp
        payoff/double_strikes/test_payoff_double_digital.cpp
)

# Link Unit_tests to core_library and GTest/GMock
target_link_libraries(Unit_tests marketdata payoff option GTest::GTest GTest::Main GTest::gmock_main )

# Register the tests for running with CTest
add_test(NAME UnitTests COMMAND Unit_tests)
