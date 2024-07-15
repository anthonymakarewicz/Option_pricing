# Find Google Test
find_package(GTest REQUIRED)

# Define the test executable
add_executable(Option_tester
        test_main.cpp
        test_market_data.cpp
        test_payoff.cpp
        mock_classes.h
        test_support.h
        ../src/payoff.cpp
        ../src/market_data.cpp
        ../src/option.cpp
        #test_option.cpp
)

# Link Google Test and Google Mock to the test executable
target_link_libraries(Option_tester GTest::GTest GTest::Main GTest::gmock_main)

# Optionally, register tests with CMake's testing system
add_test(NAME OptionTester COMMAND Option_tester)

# clang-tidy integration
set_target_properties(Option_tester PROPERTIES CXX_CLANG_TIDY "clang-tidy;-checks=*,-clang-analyzer-alpha.*")

# clang-format integration (target to check formatting)
#add_custom_target(clang-format-check
#        COMMAND find ${CMAKE_SOURCE_DIR} -name '*.cpp' -o -name '*.h' | xargs clang-format -i
#)

# Code coverage integration (optional)
if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    target_compile_options(Option_tester PRIVATE --coverage)
    target_link_libraries(Option_tester PRIVATE --coverage)
endif()