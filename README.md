# Overview

The Option Pricer project is a C++ library designed to model and price various financial options.
It complies with SOLID principles, leverages modern C++ features up to C++20 and is built on various design patterns.
The library supports a wide range of option types including vanilla, exotic, and path-dependent options.

# Features

- **Abstract Base Class**: `Option` serves as the base class for all options, ensuring a unified interface for option pricing.
- **Vanilla Options**: Supports standard options such as European and American options.
- **Exotic Options**: Supports more complex options such as Digital, Double Digital and American Options.
- **Path-Dependent Options**: Includes options that depend on the path of the underlying asset price, such as Asian, Barrier, and Lookback options.
- **Market Data Integration**: Utilizes a singleton `MarketData` class to manage and update market data for all options.
- **Payoff Functors**: Implements functor classes to represent the payoff functions of different options, including single-strike and double-strike payoffs.
- **Factory Methods**: Uses factory methods to ensure that options are always created and managed by `std::shared_ptr`.
- **Monte Carlo Solvers**: Provides a Monte Carlo solver framework supporting both path-independent and path-dependent options, with capabilities for regression-based methods like LSM (Least Squares Monte Carlo).
- **Quasi-Random Number Generators**: Includes support for advanced random number generation techniques such as Sobol and Faure sequences.

# Installation

## Prerequisites
- C++20 or higher
- CMake 3.10 or higher
- A compatible C++ compiler (e.g., g++, clang++)

## Build Instructions
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


# Project Structure

```plaintext
├── src
│   ├── market_data
│   │   ├── interface_market_data.cpp
│   │   ├── market_data.cpp
│   │   ├── market_data_observer.cpp
│   │   └── stock_data.cpp
│   ├── model
│   │   ├── base_model.cpp
│   │   └── gbm_model.cpp
│   ├── option
│   │   ├── base_option.cpp
│   │   ├── interface_option.cpp
│   │   ├── parameter_object.cpp
│   │   ├── path_dependent
│   │   │   ├── american_option.cpp
│   │   │   ├── asian_option.cpp
│   │   │   ├── barrier_option.cpp
│   │   │   ├── base_path_dependent_option.cpp
│   │   │   ├── factory_american_option.cpp
│   │   │   ├── factory_asian_option.cpp
│   │   │   ├── factory_barrier_option.cpp
│   │   │   ├── factory_lookback_option.cpp
│   │   │   └── lookback_option.cpp
│   │   └── single_path
│   │       ├── base_single_path_option.cpp
│   │       ├── digital_option.cpp
│   │       ├── double_digital_option.cpp
│   │       ├── european_option.cpp
│   │       ├── factory_digital_option.cpp
│   │       ├── factory_double_digital_option.cpp
│   │       └── factory_european_option.cpp
│   ├── payoff
│   │   ├── base_payoff.cpp
│   │   ├── double_strikes
│   │   │   ├── base_payoff_double_strikes.cpp
│   │   │   └── payoff_double_digital.cpp
│   │   ├── payoff_floating_strike_lookback.cpp
│   │   └── single_strike
│   │       ├── base_payoff_single_strike.cpp
│   │       ├── payoff_digital.cpp
│   │       └── payoff_vanilla.cpp
│   ├── random
│   │   ├── distribution
│   │   │   ├── base_distribution.cpp
│   │   │   └── standard_normal_distribution.cpp
│   │   └── number_generator
│   │       ├── base_generator.cpp
│   │       ├── base_quasi_random_generator.cpp
│   │       ├── faure_quasi_random_generator.cpp
│   │       ├── pseudo_random_generator.cpp
│   │       └── sobol_quasi_random_generator.cpp
│   └── solver
│       ├── base_solver.cpp
│       └── monte_carlo
│           ├── base_mc.cpp
│           ├── base_mc_path_dependent.cpp
│           ├── basis_function
│           │   ├── base_basis_function_strategy.cpp
│           │   ├── chebyshev.cpp
│           │   ├── laguerre.cpp
│           │   ├── legendre.cpp
│           │   └── monomial.cpp
│           ├── builder
│           │   ├── base_mc_builder.cpp
│           │   ├── base_mc_builder_path_dependent.cpp
│           │   ├── mc_builder_american.cpp
│           │   ├── mc_builder_asian.cpp
│           │   ├── mc_builder_barrier.cpp
│           │   ├── mc_builder_single_path.cpp
│           │   └── mc_lookback_builder.cpp
│           ├── mc_american.cpp
│           ├── mc_asian.cpp
│           ├── mc_barrier.cpp
│           ├── mc_lookback.cpp
│           ├── mc_single_path.cpp
│           ├── mc_solver.cpp
│           └── regression
│               ├── base_regression_strategy.cpp
│               ├── lasso.cpp
│               ├── least_squares.cpp
│               └── ridge.cpp

```

# Usage

## Creating and Pricing Options

The library allows users to create and price various types of options using both pseudo-random and quasi-random number generators.
Below is an example that demonstrates how to create and price an American put option using Monte Carlo simulation.

### 1. Initializing Market Data and Creating the Option

```cpp
using namespace OptionPricer;

std::string ticker = "AAPL";  // Ticker symbol
double T = 1.0;              // Time to maturity
double K = 100.0;           // Strike price
double S = 100.0;          // Current stock price
double sigma = 0.15;      // Volatility
double r = 0.03;         // Risk-free interest rate
int dim = 52;           // Number of time steps
double lambda = 1;     // Regularization parameter for Lasso regression

// Initialize market data
auto marketData = MarketData::getInstance();
marketData->addStock(ticker, S, sigma);
marketData->setR(r);

// Set up option parameters
ParameterObject params;
params.setParameter("ticker", ticker);
params.setParameter("T", T);
params.setParameter("K", K);

// Create American put option using factory
AmericanOptionFactory factory;
std::shared_ptr<AmericanOption> americanPut = factory.createPutOption(params);
```

### Explanation:
- **Market Data initialization**: The `MarketData` singleton is used to store and manage the current stock price, volatility, and risk-free interest rate for the asset. This data is essential for pricing the option.


- **Option Creation**: The `AmericanOptionFactory` is used to create an American put option based on the specified parameters (ticker, maturity, and strike price). This factory pattern ensures the option is created and managed correctly. 

### 2. Setting Up the Monte Carlo Components
```cpp
int dim = 150;        // Number of time steps
int numberBases = 5  // Number of basis functions

// Create Quasi Random Number Generator with Sobol sequences
std::shared_ptr<StandardNormalDistribution> normal = std::make_shared<StandardNormalDistribution>();
std::shared_ptr<SobolGenerator> generator = std::make_shared<SobolGenerator>(normal, dim);

// Create the Geometric Brownian Motion model
std::shared_ptr<GeometricBrownianMotionModel> brownianMotion = std::make_shared<GeometricBrownianMotionModel>(ticker, marketData);

// Create basis function and regularized regression for LSM (Least Squares Monte Carlo)
std::shared_ptr<LaguerreBasisFunction> laguerre = std::make_shared<LaguerreBasisFunction>(numberBases);

// Create Monte Carlo pricer through the American builder
AmericanMCBuilder americanBuilder;
std::unique_ptr<MCPricer> americanPricer = builder.setOption(americanPut)
                                                  .setBasisFunctionStrategy(laguerre)
                                                  .setSteps(dim)
                                                  .setNumberGenerator(generator).build();
```

### Explanation:

- **American Monte Carlo Builder**: This class leverages the builder design pattern to simplify the creational process for the MCPricer. It provides default implementations for most of the components except option which must be set explicitly.


- **Random Number Generator**: A SobolGenerator is used to generate quasi-random numbers, which are more effective for Monte Carlo simulations in certain scenarios due to their low discrepancy.
The default for AmericanMCBuilder is set to RandomNumberGenerator and uses pseudo-random numbers generated from Mersenne Twister.


- **Geometric Brownian Motion Model**: The GeometricBrownianMotionModel represents the stochastic process of the underlying asset.
It is the default model for AmericanMCBuilder.


- **Basis Function**: The LaguerreBasisFunction is used for the Least Squares Monte Carlo (LSM) method. This method is crucial for pricing American options, which may be exercised before maturity.

### 3. Running the Monte Carlo Simulation

```cpp
unsigned long N = 1000000 // Number of simulations
double lambda = 1;       // Regularization parameter regularized regression

// Set up the Monte Carlo solver
MCSolver mcSolver;
mcSolver.setN(N);  // Set the number of simulations
mcSolver.setPricer(std::move(americanPricer));

// Config 1: Use config from 2.
std::cout << "Config 1, P = " << mcSolver.solve() << "\n";

// Config 2: Use Chebyshev polynomials
numberBases = 10;
auto chebychev = std::shared_ptr<ChebyshevBasisFunction>(numberBases)
auto americanPricer2 = builder.setBasisFunctionStrategy(laguerre).build();
mcSolver.setPricer(std::move(americanPricer2));

std::cout << "Config 2, P = " << mcSolver.solve() << "\n";

// Config 3: Use Lasso regression 
auto lasso = std::make_shared<LassoRegression>(lambda);
auto americanPricer3 = builder.setRegressionStrategy(lasso).build();
mcSolver.setPricer(std::move(americanPricer3));

std::cout << "Config 3, P = " << mcSolver.solve() << "\n";
```

# Testing

## Tests Directory

This directory contains all the test files and configurations for the Option Pricer project. The tests are organized to ensure modularity, clarity, and ease of maintenance.

### Directory Structure
```plaintext
tests
.
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
- [Eigen 3](https://eigen.tuxfamily.org/index.php?title=Main_Page):  C++ template library for linear algebra.
- [Boost Random](https://www.boost.org/doc/libs/1_76_0/doc/html/boost_random.html): Part of the C++ Boost libraries for random number generation and probability distributions.
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
   cmake --build . # more generic than make and works with any generator
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