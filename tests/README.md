# Tests Directory

This directory contains all the test files and configurations for the Option Pricer project. The tests are organized to ensure modularity, clarity, and ease of maintenance.

## Directory Structure
```plaintext
tests
├── CMakeLists.txt
├── README.md
├── config
│   ├── mock_classes.h
│   └── test_support.h
├── test_main.cpp
├── unit
│   ├── CMakeLists.txt
│   ├── test_market_data.cpp
│   ├── test_option.cpp
│   └── test_payoff.cpp
└── integration
    ├── CMakeLists.txt
    └── test_integration_option.cpp

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
   ```
   mkdir build && cd build
   ```
3. **Configure the project with CMake**:
   ```
   cmake ..
   ```
4. **Build the project**:
   ```
   make
   ```
### Running tests
After building the project, you can run the tests using CTest:
```
ctest --output-on-failure
```
Alternatively, you can run specific tests:
- **Run all Tests**:
```
ctest -R AllTests --output-on-failure
```
- **Run only Unit Tests**:
```
ctest -R UnitTests --output-on-failure
```
- **Run only Integration Tests**:
```
ctest -R IntegrationTests --output-on-failure
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

## Directory Overview

### `config`
- **mock_classes.h**: Contains mock classes used in testing. These mocks simulate the behavior of real classes to isolate the functionality being tested.
- **test_support.h**: Additional utilities and support functions for tests.

### `unit`
- **CMakeLists.txt**: CMake configuration for unit tests.
- **test_market_data.cpp**: Unit tests for the Market Data module.
- **test_option.cpp**: Unit tests for the Option module.
- **test_payoff.cpp**: Unit tests for the Payoff module.

### `integration`
- **CMakeLists.txt**: CMake configuration for integration tests.
- **test_integration_option.cpp**: Integration test for interaction between `option.h`, `market_data.h` and `payoff.h`

### `CMakeLists.txt`
CMake configuration for running all the tests.

### `test_main.cpp`
This is the main entry point for running the tests.
It initializes the Google Test framework and runs all the test cases defined in the `unit` and `integration`directory.

## Contact
For any questions or contributions, please contact Anthony Makarewicz at [anthonymakarewicz@gmail.com].
