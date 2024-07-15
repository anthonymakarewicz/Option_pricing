cmake_minimum_required(VERSION 3.26.3)
project(Option_pricer)

# Set the version of C++ to 23
set(CMAKE_CXX_STANDARD 23)

# Set the Vcpkg toolchain file
set(CMAKE_TOOLCHAIN_FILE "/Users/anthony/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Specify where to look for header files
include_directories(include)

# Add the main executable
add_executable(Option_pricer main.cpp src/option.cpp src/payoff.cpp src/market_data.cpp)

# Enable testing
enable_testing()
add_subdirectory(tests)