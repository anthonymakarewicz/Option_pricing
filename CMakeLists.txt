cmake_minimum_required(VERSION 3.26.3)
project(Option_pricer)

# Set the version to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

# Specify the target architecture for macOS
if(APPLE)
    # Detect the processor architecture
    if(CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "arm64")
        set(CMAKE_OSX_ARCHITECTURES "arm64" CACHE STRING "Build architectures for Mac OS X" FORCE)
    elseif(CMAKE_HOST_SYSTEM_PROCESSOR STREQUAL "x86_64")
        set(CMAKE_OSX_ARCHITECTURES "x86_64" CACHE STRING "Build architectures for Mac OS X" FORCE)
    else()
        message(WARNING "Unknown architecture: ${CMAKE_HOST_SYSTEM_PROCESSOR}. Defaulting to x86_64.")
        set(CMAKE_OSX_ARCHITECTURES "x86_64" CACHE STRING "Build architectures for Mac OS X" FORCE)
    endif()
endif()


# Set the Vcpkg toolchain file
#set(CMAKE_TOOLCHAIN_FILE "/Users/anthony/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake"
#        CACHE STRING "Vcpkg toolchain file")

find_package(Boost REQUIRED COMPONENTS random)
find_package(Eigen3 REQUIRED)

# Check if random has been found before compiling src
if (Boost_FOUND)
    message(STATUS "Boost found: ${Boost_VERSION}")
    # Ensure Boost include directories are added
    include_directories(${Boost_INCLUDE_DIRS})
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
)

# Create dynamic library for payoff
add_library(payoff SHARED
        src/payoff/base_payoff.cpp
        src/payoff/payoff_floating_strike_lookback.cpp
        src/payoff/single_strike/base_payoff_single_strike.cpp
        src/payoff/single_strike/payoff_vanilla.cpp
        src/payoff/single_strike/payoff_digital.cpp
        src/payoff/double_strikes/base_payoff_double_strikes.cpp
        src/payoff/double_strikes/payoff_double_digital.cpp
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
        src/option/path_dependent/asian_option.cpp
        src/option/path_dependent/barrier_option.cpp
        src/option/path_dependent/lookback_option.cpp
        # Factories
        src/option/single_path/factory_european_option.cpp
        src/option/single_path/factory_digital_option.cpp
        src/option/single_path/factory_double_digital_option.cpp
        src/option/path_dependent/factory_american_option.cpp
        src/option/path_dependent/factory_asian_option.cpp
        src/option/path_dependent/factory_barrier_option.cpp
        src/option/path_dependent/factory_lookback_option.cpp
)

# Create dynamic library for model
add_library(model SHARED
        src/model/gbm_model.cpp
        src/model/base_model.cpp
        src/model/heston_model.cpp
        src/model/discretization/base_cir_discretization.cpp
        src/model/discretization/explicit_euler_cir_discretization.cpp
        src/model/discretization/milstein_cir_discretization.cpp
        src/model/merton_jump_diffusion_model.cpp
        src/model/kou_model.cpp
        src/model/variance_gamma_model.cpp
)

# Create dynamic library for random
add_library(random SHARED
        src/random/distribution/base_distribution.cpp
        src/random/distribution/standard_normal_distribution.cpp
        src/random/number_generator/base_generator.cpp
        src/random/number_generator/pseudo_random_generator.cpp
        src/random/number_generator/base_quasi_random_generator.cpp
        src/random/number_generator/faure_quasi_random_generator.cpp
        src/random/number_generator/sobol_quasi_random_generator.cpp
        src/random/distribution/poisson_distrib.cpp
        src/random/distribution/normal_distrib.cpp
        src/random/distribution/continuous_uniform_distrib.cpp
        src/random/distribution/exponential_distr.cpp
        src/random/distribution/gamma_distrib.cpp
)

# Create dynamic library for solver
add_library(solver SHARED
        src/solver/base_solver.cpp
        src/solver/monte_carlo/mc_solver.cpp
        src/solver/monte_carlo/base_mc.cpp
        src/solver/monte_carlo/mc_single_path.cpp
        src/solver/monte_carlo/mc_asian.cpp
        src/solver/monte_carlo/mc_barrier.cpp
        src/solver/monte_carlo/mc_lookback.cpp
        src/solver/monte_carlo/mc_american.cpp
        src/solver/monte_carlo/builder/base_mc_builder.cpp
        src/solver/monte_carlo/builder/mc_builder_single_path.cpp
        src/solver/monte_carlo/builder/mc_builder_asian.cpp
        src/solver/monte_carlo/builder/mc_builder_barrier.cpp
        src/solver/monte_carlo/builder/mc_builder_american.cpp
        src/solver/monte_carlo/builder/mc_lookback_builder.cpp
        src/solver/monte_carlo/regression/base_regression_strategy.cpp
        src/solver/monte_carlo/regression/least_squares.cpp
        src/solver/monte_carlo/regression/ridge.cpp
        src/solver/monte_carlo/regression/lasso.cpp
        src/solver/monte_carlo/basis_function/base_basis_function_strategy.cpp
        src/solver/monte_carlo/basis_function/monomial.cpp
        src/solver/monte_carlo/basis_function/legendre.cpp
        src/solver/monte_carlo/basis_function/legendre.cpp
        src/solver/monte_carlo/basis_function/chebyshev.cpp
        src/solver/monte_carlo/basis_function/laguerre.cpp
)

target_link_libraries(option PUBLIC marketdata payoff)
target_link_libraries(model PUBLIC option random)
target_link_libraries(solver PUBLIC option model Boost::random Eigen3::Eigen)

# Create main executable
add_executable(Option_pricer main.cpp)

# Link the main executable to our dynamic libraries
target_link_libraries(Option_pricer PUBLIC marketdata payoff option solver random model)

# Enable testing and add the tests directory
enable_testing()
add_subdirectory(tests)

# Add the examples subdirectory
add_subdirectory(examples)