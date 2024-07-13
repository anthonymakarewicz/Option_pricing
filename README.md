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
