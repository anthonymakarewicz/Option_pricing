cmake_minimum_required(VERSION 3.26.3)
project(Option_pricer)

# Set the version of C++ to 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set the Vcpkg toolchain file
set(CMAKE_TOOLCHAIN_FILE "/Users/anthony/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Specify where to look for header files
include_directories(include)

# Add the main executable
add_executable(Option_pricer main.cpp
        src/market_data/interface_market_data.cpp
        src/market_data/market_data.cpp
        src/market_data/market_data_observer.cpp
        src/market_data/stock_data.cpp
        src/option/interface_option.cpp
        src/option/base_option.cpp
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
)

# Enable testing
enable_testing()
add_subdirectory(tests)

#[[
# clang-tidy integration
find_program(CLANG_TIDY_EXECUTABLE NAMES clang-tidy)
if(CLANG_TIDY_EXECUTABLE)
    set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXECUTABLE};-checks=*,-clang-analyzer-alpha.*")
endif()
]]

#[[
# clang-format integration (target to check formatting)
add_custom_target(clang-format-check
       COMMAND find ${CMAKE_SOURCE_DIR} -name '*.cpp' -o -name '*.h' | xargs clang-format -i
)
]]

#[[
# Code coverage integration (optional)
if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
   target_compile_options(Option_pricer PRIVATE --coverage)
   target_link_libraries(Option_pricer PRIVATE --coverage)
endif()
]]