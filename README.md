# Option Pricing Library

## Overview

The Option Pricer project is a C++ library designed to model and price various financial options.
It complies with SOLID principles, leverages modern C++ features up to C++20 and is built on various design patterns to improve the maintainability and extensibility of the project.
The library supports pricing for both vanilla European options and more exotic, path-dependent options, using multiple pricing methods, including Monte Carlo simulations and Finite Difference Methods (FDM).

## Modules

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

### Dependencies
- [Eigen 3](https://eigen.tuxfamily.org/index.php?title=Main_Page):  C++ template library for linear algebra.
- [Boost Random](https://www.boost.org/doc/libs/1_76_0/doc/html/boost_random.html): Part of the C++ Boost libraries for random number generation and probability distributions.
- [Google Test (GTest)](https://github.com/google/googletest): A popular C++ testing framework.
- [Google Mock](https://github.com/google/googletest/tree/main/googlemock): A library for writing and using C++ mock classes.


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

// Create a European call option using factory
EuropeanOptionFactory europeanFactory;
std::shared_ptr<Option> europeanCall = europeanFactory.createCallOption(params);

// Create American put option using factory
AmericanOptionFactory factory;
std::shared_ptr<AmericanOption> americanPut = factory.createPutOption(params);
```

### 2. Pricing an European call option with Finite Difference Method

```cpp
using namespace PDE::OneFactor;
using namespace FDM::OneFactor;

double xDom = 2.0 * K;      // Stock price range [0.0 , 2*K]
double tDom = T;           // Time period as for the option
unsigned long J = 200;    // Number of steps for the stock price
unsigned long N = 200;  // Number of time steps 

// Configurations
std::shared_ptr<Interpolation> quadrInterp = std::make_shared<QuadraticInterpolation>();
std::shared_ptr<MatrixSolver> thomas = std::make_shared<ThomasAlgorithm>();

// Set up the Crank Nicolson solver
std::shared_ptr<ConvectionDiffusionPDE> pde = std::make_unique<BlackScholesPDE>(europeanCall, marketData);
CrankNicolsonFDMSolver fdm(xDom, J, tDom, N, std::move(pde), europeanCall, marketData, quadrInterp, thomas);

// Vector of solutions
std::vector<double> prices = fdm.solve();

// Interpolated price
double price = fdm.calculatePrice();

std::cout << "Price for an European call with FDM: " << price << "\n";
```

### 3. Pricing an American Put Option Using Monte Carlo Simulation
```cpp
unsigned long N = 1000000  // Number of simulations
int dim = 150;            // Number of time steps
int numberBases = 5      // Number of basis functions
double theta = -0.005;  // Drift of the Brownian motion
double nu = 0.5;       // Variance rate of the Gamma process

// Configurations
std::shared_ptr<SobolGenerator> auto prng = std::make_shared<PseudoRandomNumberGenerator>(dim);
std::shared_ptr<VarianceGammaModel> brownianMotion = std::make_shared<GeometricBrownianMotionModel>(ticker, marketData);
std::shared_ptr<LaguerreBasisFunction> laguerre = std::make_shared<LaguerreBasisFunction>(numberBases);

// Create Monte Carlo pricer through the American builder
AmericanMCBuilder americanBuilder;
std::unique_ptr<MCPricer> americanPricer = builder.setOption(americanPut)
                                                  .setBasisFunctionStrategy(laguerre)
                                                  .setNumberGenerator(prng)
                                                  .build();
                                                  
// Set up the Monte Carlo solver
MCSolver mcSolver;
mcSolver.setN(N);  // Set the number of simulations
mcSolver.setPricer(std::move(americanPricer));   

double price = mcSolver.solve()
std::cout << "Price for an American Put with MC: " << price << "\n";                                       
```

## Testing
For more detailed information on unit and integration tests, [see the full testing instructions here.](tests/README.md)

## Contributing

Contributions are welcome! 
For more detailed information on the C++ and Git guidelines, [see the full contribution directives here.](tests/README.md)

## License
This project is licensed under the MIT License. See the LICENSE file for details.