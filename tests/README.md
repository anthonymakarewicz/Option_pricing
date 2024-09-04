# Testing the Option Pricing Library

This directory contains all test files and configurations for the Option Pricer project. The tests ensure that the library remains robust and free of regressions as new features are added or existing functionality is updated.

- **Unit tests**: Validate the behavior of individual components and modules.
- **Integration tests**: Ensure that modules work together as expected.

Please note that the basic structure for the tests has been implemented. 
Contributors are encouraged to add specific tests for new modules or enhance the existing tests to ensure full coverage.
## Directory Structure
```plaintext
tests
├── CMakeLists.txt
├── README.md
├── integration
│   ├── CMakeLists.txt
│   └── test_integration_option.cpp
├── test_main.cpp
└── unit
    ├── CMakeLists.txt
    ├── market_data
    │   ├── test_market_data.cpp
    │   └── test_stock_data.cpp
    ├── option
    │   ├── test_base_option.cpp
    │   ├── test_european_option.cpp
    │   └── test_factory_european_option.cpp
    ├── payoff
    │   ├── double_strikes
    │   │   └── test_payoff_double_digital.cpp
    │   └── single_strike
    │       ├── test_payoff_digital.cpp
    │       ├── test_payoff_vanilla.cpp
    │       └── test_support
    │           ├── common_payoff_single_strike_tests.h
    │           └── fixture_payoff_single_strike.h
    └── test_support
        └── mock_classes.h
```


## Building and Running Tests

### Prerequisites
Make sure you have CMake and GTest installed. You can install GTest using a package manager or
through [vcpkg](https://github.com/microsoft/vcpkg).

### Build Instructions

1. **Navigate to the project root directory**:
   ```sh
   cd path/to/your/project
   ```
2. **Create a build directory**:
   ```sh
   mkdir build && cd build
   ```
3. **Configure the project with CMake**:
   ```sh
   cmake ..
   ```
4. **Build the project**:
   ```sh
   cmake --build .
   ```

### Running tests with Ctest

For automated testing or integration,
you can run the all the tests executable using CTest:
```sh
ctest --output-on-failure
```

Alternatively, you can run specific tests:
- **Run only Unit Tests**:
```sh
ctest -R UnitTests --output-on-failure
```
- **Run only Integration Tests**:
```sh
ctest -R IntegrationTests --output-on-failure
```

### Running the Custom Tests Target
You can also run all the tests at once by using the custom target **Tests**.
For that purpose, you can build and run the Tests target as follows:
1. **Build the custom Tests target**:
```sh
cmake --build . --target Tests
```
2. **Run the custom Tests target**:
```sh
ctest -R Tests --output-on-failure
```

### Running tests with GTest
For detailed output, running the test using GTest can be a good approach for local
development and debugging.
1. **Go to the build directory**:
```sh
cd build
```
2. **Run the unit tests executable**:
```sh
./tests/unit/Unit_tests
```
3. **Run the integration tests executable**:
```sh
./tests/integration/Integration_tests
```

## Adding New Tests

### Create a new test file:
Add your new test file in the appropriate directory:
- For unit tests: Add the file to the `unit` directory.
- For integration tests: Add the file to the `integration` directory.

### Modify CMakeLists.txt
Make sure to include the new test file in the respective `CMakeLists.txt`:
- For **unit tests**, add the new test file in the `add_executable` and `target_link_libraries` sections of the `unit/CMakeLists.txt`:
   ```cmake
   add_executable(Unit_tests ${CMAKE_CURRENT_SOURCE_DIR}/../test_main.cpp
       # Other test files...
       option/test_new_option.cpp)
   target_link_libraries(Unit_tests marketdata payoff option GTest::GTest GTest::Main GTest::gmock_main)
### Write Test Cases:
Use GTest and Google Mock to write your test cases. Refer to the [GTest documentation](https://github.com/google/googletest/blob/main/googletest/docs/primer.md) for more details.


## Contact
For any questions or contributions, please contact Anthony Makarewicz at [anthonymakarewicz@gmail.com].