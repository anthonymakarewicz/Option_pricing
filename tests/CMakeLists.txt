# Top-level CMake configuration for tests
enable_testing()

# Add subdirectories for unit and integration tests
add_subdirectory(unit)
add_subdirectory(integration)

# Custom target that runs all tests at once using CTest
add_custom_target(Tests
        COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIG> --output-on-failure
        DEPENDS Unit_tests Integration_tests
)