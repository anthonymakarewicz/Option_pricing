# Option Pricer

## Overview

The Option Pricer project is a C++ library designed to model and price various financial options. It leverages modern C++ practices such as smart pointers, factory methods, and the observer pattern to manage market data and calculate option prices efficiently. The library supports a wide range of option types including vanilla, exotic, and path-dependent options.

## Features

- **Abstract Base Class**: `Option` serves as the base class for all options, ensuring a unified interface for option pricing.
- **Vanilla Options**: Supports standard options such as European and American options.
- **Exotic Options**: Supports more complex options such as Digital and Double Digital options.
- **Path-Dependent Options**: Includes options that depend on the path of the underlying asset price, such as Asian options.
- **Market Data Integration**: Utilizes a singleton `MarketData` class to manage and update market data for all options.
- **Payoff Functors**: Implements functor classes to represent the payoff functions of different options.
- **Factory Methods**: Uses factory methods to ensure that options are always created and managed by `std::shared_ptr`.

## Project Structure

```plaintext
├── include
│   ├── option.h
│   ├── vanilla_option.h
│   ├── exotic_option.h
│   ├── market_data.h
│   ├── payoff.h
│   ├── observer.h
├── src
│   ├── option.cpp
│   ├── vanilla_option.cpp
│   ├── exotic_option.cpp
│   ├── market_data.cpp
│   ├── payoff.cpp
│   ├── observer.cpp
├── tests
│   ├── option_tests.cpp
│   ├── market_data_tests.cpp
│   ├── payoff_tests.cpp
├── CMakeLists.txt
└── README.md
```

## Installation

### Prerequisites
 - C++17 or higher
 - CMake 3.10 or higher 
 - A compatible C++ compiler (e.g., g++, clang++)

### Build Instructions
1. Clone the repository:
```
git clone https://github.com/anthonymakarewicz/option_pricer.git
cd option_pricer
```

2. Create a build directory and run CMake:
```
mkdir build
cd build
cmake ..
```

3. Build the project:
```
make
```

4. Run the tests:
```
make test
```

## Usage

### Creating Options
Options are created using factory methods to ensure they are managed by `std::shared_ptr`. <br>
Here is an example of creating a VanillaOption (EuropeanOption) using the factory method:

#### Example: Creating a VanillaOption 
The following example demonstrates how to create a VanillaOption (EuropeanOption) using the factory method.
The example also shows how to handle potential exceptions that may be thrown during the creation and use of the Option.

```
#include <iostream>
#include "vanilla_option.h"
#include "payoff.h"

int main() {
    VanillaOptionFactory factory;

    try {
        // Create a valid Payoff object
        auto payoff = std::make_unique<PayoffCall>(100.0);
        // Use the factory to create a VanillaOption
        auto option = factory.createOption("AAPL", std::move(payoff), 1.0);
        std::cout << *option << std::endl; // Output the option details

        // Attempt to create an invalid Payoff object
        auto invalidPayoff = std::make_unique<PayoffDoubleDigital>(90.0, 110.0);
        // This will throw an exception since VanillaOption only supports PayoffSingleStrike
        auto invalidOption = factory.createOption("AAPL", std::move(invalidPayoff), 1.0);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl; // Handle invalid argument exceptions
    } catch (const std::runtime_error& e) {
        std::cerr << "Runtime error: " << e.what() << std::endl; // Handle runtime errors
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl; // Handle all other exceptions
    }

    return 0;
}
```

### Market Data Updates
Market data updates are managed by the `MarketData` class.
When market data changes, all registered options are notified and can update their prices accordingly.

```
#include "market_data.h"
#include "vanilla_option.h"

// Example usage
void updateMarketData() {
auto marketData = MarketData::getInstance();
marketData->updateStockPrice("AAPL", 150.0);
marketData->updateStockSigma("AAPL", 0.25);
}
```

## Testing

Unit tests are located in the `tests` directory.
To run the tests, use the following command in the build directory:

```
make test
```

Tests are written using Google Test as testing framework.
Ensure the testing framework is properly configured in the `CMakeLists.txt.

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request for any improvements or bug fixes.

### Code Style
- Follow the C++ Core Guidelines. 
- Use modern C++ practices. 
- Ensure all new code is covered by unit tests.

### Reporting Issues
If you encounter any issues, please create a new issue on GitHub with a detailed description of the problem.

## License
This project is licensed under the MIT License. See the LICENSE file for details.