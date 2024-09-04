# Integration tests configuration
find_package(GTest REQUIRED)

# Create executable for running integration tests
add_executable(Integration_tests ${CMAKE_CURRENT_SOURCE_DIR}/../test_main.cpp
        test_integration_option.cpp
)

# Link the Integration_tests executable to the already compiled source code
target_link_libraries(Integration_tests marketdata payoff option GTest::GTest GTest::Main GTest::gmock_main)

# Register the tests for running with CTest
add_test(NAME IntegrationTests COMMAND Integration_tests)
