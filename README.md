# Option Pricing Library

[![Push CI](https://github.com/anthonymakarewicz/Option_pricing/actions/workflows/push_ci.yml/badge.svg)](https://github.com/anthonymakarewicz/Option_pricing/actions/workflows/push_ci.yml)
[![Pull Request CI](https://github.com/anthonymakarewicz/Option_pricing/actions/workflows/pr_ci.yml/badge.svg)](https://github.com/anthonymakarewicz/Option_pricing/actions/workflows/pr_ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE.txt)
![GitHub last commit](https://img.shields.io/github/last-commit/anthonymakarewicz/Option_pricing)

## Overview
The **Option Pricer** is a C++ library designed to model and price various financial options, such as European, American, and exotic path-dependent options (e.g., Asian, Barrier).
It is optimized for financial institutions, quantitative analysts, and researchers who need fast, flexible, and accurate option pricing methods.

This library complies with **SOLID** principles and leverages modern C++ features (up to C++20).
It incorporates various design patterns to ensure maintainability and extensibility.
The library supports multiple pricing methods, including **Monte Carlo simulations** and **Finite Difference Methods (FDM)**, giving users the flexibility to select the most appropriate solver for their needs.

## Table of Contents
1. [Overview](#overview)
2. [Modules](#modules)
3. [Installation](#installation)
4. [Usage](#usage)
5. [Tests](#tests)
6. [Contributing](#contributing)
7. [License](#license)

## Modules

The library is divided into several modules to improve maintainability and flexibility. Each module is responsible for handling a specific aspect of the option pricing process. Below are the key modules:


- **`Option`**: Defines various option types, including both single-path options (e.g., European, Digital) and path-dependent options (e.g., Asian, Barrier). Provides factory methods for option creation and parameter management.


- **`Payoff`**: Encapsulates payoff logic using functors. It includes different structures like single-strike, double-strike, and exotic payoffs (e.g., lookbacks).


- **`MarketData`**: Manages and updates market data, such as stock prices, volatility, and risk-free rates, using a singleton design pattern.


- **`Random`**: Provides random number generators, including pseudo-random (Mersenne Twister) and quasi-random sequences (Sobol and Faure).


- **`Numerical Analysis`**: Provides tools for regression, interpolation, and matrix solvers, which are essential for methods like Least Squares Monte Carlo (LSM) and Finite Difference Methods (FDM).


- **`Model`**: Implements different stochastic models, such as the Geometric Brownian Motion (GBM), Heston model, and Variance Gamma model, used to simulate stock price paths for Monte Carlo simulations.


- **`Solver`**: Contains both Monte Carlo and Finite Difference solvers. The Monte Carlo solver supports path-independent and path-dependent options. The FDM solver supports multiple schemes, including **Euler Explicit**, **Fully Implicit**, and **Crank-Nicolson**.

For a detailed overview of the project structure, [see the full structure here](docs/project_structure.md).


## Installation

### Prerequisites
- C++20 or higher
- CMake 3.10 or higher
- A compatible C++ compiler (e.g., g++, clang++)
- **Dependencies**:
    - [Eigen 3](https://eigen.tuxfamily.org/index.php?title=Main_Page): (version 3.3.7+)
    - [Boost Random](https://www.boost.org/doc/libs/1_76_0/doc/html/boost_random.html): (version 1.70.0+)
    - [Google Test (GTest)](https://github.com/google/googletest): (version 1.10.0+)
    - [Google Mock](https://github.com/google/googletest/tree/main/googlemock)

You can install Eigen and Boost through [vcpkg](https://github.com/microsoft/vcpkg):

```bash
vcpkg install eigen3 boost-random gtest
```

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

Below is an example that demonstrates how to create and price an an European call option using Finite Difference Method,
and an American put option using Monte Carlo simulation.

### 1. Initializing Market Data and Creating the Options

```cpp
using namespace OptionPricer;

std::string ticker = "AAPL";  // Ticker symbol
double T = 1.0;              // Time to maturity
double K = 100.0;           // Strike price
double S = 100.0;          // Current stock price
double sigma = 0.15;      // Volatility
double r = 0.03;         // Risk-free interest rate

// Initialize market data
auto marketData = MarketData::getInstance();
marketData->addStock(ticker, S, sigma);
marketData->setR(r);

// Set up option parameters
ParameterObject params;
params.setParameter("ticker", ticker);
params.setParameter("T", T);
params.setParameter("K", K);

// Create a European call and American Put using the factory method
EuropeanOptionFactory europeanFactory;
AmericanOptionFactory factory;
std::shared_ptr<Option> europeanCall = europeanFactory.createCallOption(params);
std::shared_ptr<AmericanOption> americanPut = factory.createPutOption(params);
```

### 2. Pricing an European call option with Finite Difference Method

```cpp
using namespace PDE::OneFactor;
using namespace FDM::OneFactor;

double xDom = 2.0 * K;     // Stock price range [0.0 , 2*K]
double tDom = T;          // Time period as for the option
unsigned long J = 200;   // Number of steps for the stock price
unsigned long N = 200;  // Number of time steps 

// Configurations
auto quadrInterp = std::make_shared<QuadraticInterpolation>();
auto thomas = std::make_shared<ThomasAlgorithm>();

// Set up the Crank Nicolson solver
auto pde = std::make_unique<BlackScholesPDE>(europeanCall, marketData);
CrankNicolsonFDMSolver fdm(xDom, J, tDom, N, std::move(pde),
                           europeanCall, marketData, quadrInterp, thomas);

double price = fdm.calculatePrice();
std::cout << "Price for an European call with FDM: " << price << "\n";
```

### 3. Pricing an American Put Option Using Monte Carlo Simulation
```cpp
unsigned long N = 1000000  // Number of simulations
int dim = 150;            // Number of time steps
int nBases = 5           // Number of basis functions
double theta = -0.005;  // Drift of the Brownian motion
double nu = 0.5;       // Variance rate of the Gamma process

// Configurations
auto prng = std::make_shared<PseudoRandomNumberGenerator>(dim);
auto vg = std::make_shared<VarianceGammaModel>(ticker, marketData, nu, theta);
auto laguerre = std::make_shared<LaguerreBasisFunction>(nBases);

// Create Monte Carlo pricer through the American builder
AmericanMCBuilder americanBuilder;
std::unique_ptr<MCPricer> americanPricer = builder.setOption(americanPut)
                                                  .setStockPriceModel(vg)
                                                  .setBasisFunctionStrategy(laguerre)
                                                  .build();
                                                  
// Set up the Monte Carlo solver
MCSolver mcSolver;
mcSolver.setN(N); 
mcSolver.setPricer(std::move(americanPricer));   

double price = mcSolver.solve()
std::cout << "Price for an American Put with MC: " << price << "\n";                                       
```

## Tests
This project includes both unit and integration tests to ensure robustness.

### Running Tests

Once the project is built, you can run all tests using CTest:

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

For detailed information on how to run specific tests, or instructions for adding new tests [see the full testing instructions here.](tests/README.md)

## Contributing

Contributions are welcome! If you find any issues or want to improve the library, please fork the repository and submit a pull request.

### Guidelines:
- Follow the C++ Core Guidelines.
- Ensure new features or bug fixes are covered by unit tests.
- Create a new issue on GitHub for bug reports, feature requests, or discussions.

For more detailed information on the C++ and Git guidelines, [see the full contribution directives here.](tests/README.md)

## License
This project is licensed under the MIT License. [See the LICENSE file for details.](LICENSE.txt)