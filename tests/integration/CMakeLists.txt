# Integration tests configuration
find_package(GTest REQUIRED)

add_executable(Integration_tests
        ${CMAKE_CURRENT_SOURCE_DIR}/../test_main.cpp
        test_integration_option.cpp
)

target_link_libraries(Integration_tests GTest::GTest GTest::Main GTest::gmock_main)
# Register the tests for running with CTest
add_test(NAME IntegrationTests COMMAND Integration_tests)

#[[
# clang-tidy integration
find_program(CLANG_TIDY_EXECUTABLE NAMES clang-tidy)
if(CLANG_TIDY_EXECUTABLE)
    set_target_properties(Integration_tests PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_EXECUTABLE};-checks=*,-clang-analyzer-alpha.*")
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
    target_compile_options(Integration_tests PRIVATE --coverage)
    target_link_libraries(Integration_tests PRIVATE --coverage)
endif()
]]