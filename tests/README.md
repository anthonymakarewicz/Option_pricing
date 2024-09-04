# Testing the Option Pricing Library

This directory contains all the test files and configurations for the Option Pricer project. The tests are organized to ensure modularity, clarity, and ease of maintenance.

Please note that currently only the skeleton of the tests has been implemented but can be easily extended to add new tests.

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

## Dependencies

- [Google Test (GTest)](https://github.com/google/googletest): A popular C++ testing framework.
- [Google Mock](https://github.com/google/googletest/tree/main/googlemock): A library for writing and using C++ mock classes.

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
Add your test file in the appropriate directory.
For example, to add unit tests for a new module, place the file in the `unit` directory.
For integration tests, place the file in the `integration` directory

### Include the test in CMake:
Edit the `CMakeLists.txt` file to include your new test file in the `add_executable` and `target_link_libraries` sections.

### Write Test Cases:
Use GTest and Google Mock to write your test cases. Refer to the [GTest documentation](https://github.com/google/googletest/blob/main/googletest/docs/primer.md) for more details.


## Contact
For any questions or contributions, please contact Anthony Makarewicz at [anthonymakarewicz@gmail.com].