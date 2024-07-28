# Unit tests configuration
find_package(GTest REQUIRED)

# Create the executable called Unit_tests
add_executable(Unit_tests ${CMAKE_CURRENT_SOURCE_DIR}/../test_main.cpp
        market_data/test_stock_data.cpp
        market_data/test_market_data.cpp
        payoff/single_strike/vanilla/test_payoff_vanilla_call.cpp
        payoff/single_strike/vanilla/test_payoff_vanilla_put.cpp
        payoff/single_strike/digital/test_payoff_digital_call.cpp
        payoff/single_strike/digital/test_payoff_digital_put.cpp
        payoff/double_strikes/test_payoff_double_digital.cpp
        # Add the necessary source files
        ../../src/market_data/market_data.cpp
        ../../src/market_data/market_data_observer.cpp
        ../../src/market_data/stock_data.cpp
        ../../src/option/options/base_option.cpp
        ../../src/option/options/single_path/base_single_path_option.cpp
        ../../src/option/options/single_path/european_option.cpp
        ../../src/option/options/single_path/digital/digital_option.cpp
        ../../src/option/options/single_path/digital/double_digital_option.cpp
        ../../src/option/options/path_dependent/base_path_dependent_option.cpp
        ../../src/option/options/path_dependent/american_option.cpp
        ../../src/option/options/path_dependent/asian/base_asian_option.cpp
        ../../src/option/options/path_dependent/asian/arithmetic_asian_option.cpp
        ../../src/option/options/path_dependent/asian/geometric_asian_option.cpp
        ../../src/option/options/path_dependent/barrier/base_barrier_option.cpp
        ../../src/option/options/path_dependent/barrier/knock_behavior.cpp
        ../../src/option/options/path_dependent/barrier/double_barrier.cpp
        ../../src/option/options/path_dependent/barrier/single_barrier/base_single_barrier_option.cpp
        ../../src/option/options/path_dependent/barrier/single_barrier/up_single_barrier_option.cpp
        ../../src/option/options/path_dependent/barrier/single_barrier/down_single_barrier_option.cpp
        ../../src/payoff/base_payoff.cpp
        ../../src/payoff/single_strike/base_payoff_single_strike.cpp
        ../../src/payoff/single_strike/vanilla/base_payoff_vanilla.cpp
        ../../src/payoff/single_strike/vanilla/payoff_vanilla_call.cpp
        ../../src/payoff/single_strike/vanilla/payoff_vanilla_put.cpp
        ../../src/payoff/single_strike/digital/base_payoff_digital.cpp
        ../../src/payoff/single_strike/digital/payoff_digital_call.cpp
        ../../src/payoff/single_strike/digital/payoff_digital_put.cpp
        ../../src/payoff/double_strikes/base_payoff_double_strikes.cpp
        ../../src/payoff/double_strikes/payoff_double_digital.cpp
        option/test_base_option.cpp
        option/test_european_option.cpp
)

target_link_libraries(Unit_tests GTest::GTest GTest::Main GTest::gmock_main)
# Register the tests for running with CTest
add_test(NAME UnitTests COMMAND Unit_tests)



# clang-tidy integration
#[[
find_program(CLANG_TIDY_EXECUTABLE NAMES clang-tidy)
if(CLANG_TIDY_EXECUTABLE)
    set_target_properties(Unit_tests PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_EXECUTABLE};-checks=*,-clang-analyzer-alpha.*")
endif()
]]

#[[
# clang-format integration (target to check formatting)
add_custom_target(clang-format-check
        COMMAND find ${CMAKE_SOURCE_DIR} -name '*.cpp' -o -name '*.h' | xargs clang-format -i
)
]]

#[[
# Code coverage integration (optional)
if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
     target_compile_options(Unit_tests PRIVATE --coverage)
     target_link_libraries(Unit_tests PRIVATE --coverage)
endif()
]]