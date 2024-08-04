cmake_minimum_required(VERSION 3.26.3)
project(Option_pricer)

# Set the version to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

# Set the Vcpkg toolchain file
set(CMAKE_TOOLCHAIN_FILE "/Users/anthony/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")

find_package(Boost REQUIRED COMPONENTS random)

# Check if random has been found before compiling src
if (Boost_FOUND)
    message(STATUS "Boost found: ${Boost_VERSION}")
else()
    message(FATAL_ERROR "Boost not found!")
endif()

# Specify where to look for header files
include_directories(include)

# Set the output directories for the libraries and executables
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Create dynamic library for marketdata
add_library(marketdata SHARED
        src/market_data/interface_market_data.cpp
        src/market_data/market_data.cpp
        src/market_data/market_data_observer.cpp
        src/market_data/stock_data.cpp
        include/solver/base_solver.h
)

# Create dynamic library for payoff
add_library(payoff SHARED
        src/payoff/base_payoff.cpp
        src/payoff/single_strike/base_payoff_single_strike.cpp
        src/payoff/single_strike/base_payoff_vanilla.cpp
        src/payoff/single_strike/payoff_vanilla_call.cpp
        src/payoff/single_strike/payoff_vanilla_put.cpp
        src/payoff/single_strike/base_payoff_digital.cpp
        src/payoff/single_strike/payoff_digital_call.cpp
        src/payoff/single_strike/payoff_digital_put.cpp
        src/payoff/double_strikes/base_payoff_double_strikes.cpp
        src/payoff/double_strikes/payoff_double_digital.cpp
        # Factories
        src/payoff/single_strike/factory_payoff_vanilla.cpp
        src/payoff/single_strike/factory_payoff_digital.cpp
        src/payoff/double_strikes/factory_payoff_double_digital.cpp
)

# Create dynamic library for option, linking against marketdata and payoff
add_library(option SHARED
        src/option/interface_option.cpp
        src/option/base_option.cpp
        src/option/parameter_object.cpp
        src/option/single_path/base_single_path_option.cpp
        src/option/single_path/european_option.cpp
        src/option/single_path/digital_option.cpp
        src/option/single_path/double_digital_option.cpp
        src/option/path_dependent/base_path_dependent_option.cpp
        src/option/path_dependent/american_option.cpp
        src/option/path_dependent/asian/base_asian_option.cpp
        src/option/path_dependent/asian/arithmetic_asian_option.cpp
        src/option/path_dependent/asian/geometric_asian_option.cpp
        src/option/path_dependent/barrier/base_barrier_option.cpp
        src/option/path_dependent/barrier/knock_behavior.cpp
        src/option/path_dependent/barrier/double_barrier.cpp
        src/option/path_dependent/barrier/base_single_barrier_option.cpp
        src/option/path_dependent/barrier/up_single_barrier_option.cpp
        src/option/path_dependent/barrier/down_single_barrier_option.cpp
        # Factories
        src/option/factory_option.cpp
        src/option/single_path/factory_european_option.cpp
        src/option/single_path/factory_digital_option.cpp
        src/option/single_path/factory_double_digital_option.cpp
        src/option/path_dependent/factory_american_option.cpp
        src/option/path_dependent/asian/factory_arithmetic_asian_option.cpp
        src/option/path_dependent/asian/factory_geometric_asian_option.cpp
        src/option/path_dependent/barrier/factory_up_single_barrier_option.cpp
)

# Create dynamic library for marketdata
add_library(solver SHARED
        src/solver/base_solver.cpp
        src/solver/monte_carlo/mc_solver.cpp
        include/solver/monte_carlo/mc_base_strategy.h
        src/solver/monte_carlo/mc_base_strategy.cpp
        include/solver/monte_carlo/stock_price_model.h
        src/solver/monte_carlo/stock_price_model.cpp
        src/solver/monte_carlo/gbm_stock_price_model.cpp
        include/solver/monte_carlo/gbm_stock_price_model.h

)

# Link random library to the solver ONLY
#target_link_libraries(solver PRIVATE Boost::random)

# Link the option library against marketdata and payoff
target_link_libraries(option PUBLIC marketdata payoff)

# Create main executable
add_executable(Option_pricer main.cpp)

# Link the main executable to our dynamic libraries
target_link_libraries(Option_pricer Boost::random marketdata payoff option solver)
#target_link_libraries(Option_pricer Boost::random)

# Enable testing and add the tests directory
enable_testing()
add_subdirectory(tests)

# Add the examples subdirectory
add_subdirectory(examples)