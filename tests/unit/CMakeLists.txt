# Unit tests configuration
find_package(GTest REQUIRED)

# Create the executable called Unit_tests
add_executable(Unit_tests
        ${CMAKE_CURRENT_SOURCE_DIR}/../test_main.cpp
        test_market_data.cpp
        #test_option.cpp
        test_payoff.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../config/mock_classes.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../config/test_support.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../../src/market_data.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../../src/option.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../../src/payoff.cpp
        test_option.cpp
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