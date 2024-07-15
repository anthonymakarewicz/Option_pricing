cmake_minimum_required(VERSION 3.26.3)
project(Option_pricer)

# Set the version of C++ to 23 (using the alias c++2b for compatibility with clang-tidy)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set the Vcpkg toolchain file
set(CMAKE_TOOLCHAIN_FILE "/Users/anthony/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Specify where to look for header files
include_directories(include)

# Add the main executable
add_executable(Option_pricer main.cpp src/option.cpp src/payoff.cpp src/market_data.cpp)

# Enable testing
enable_testing()
add_subdirectory(tests)

# clang-tidy integration
set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*,-clang-analyzer-alpha.*")

# clang-format integration (target to check formatting)
#add_custom_target(clang-format-check
#        COMMAND find ${CMAKE_SOURCE_DIR} -name '*.cpp' -o -name '*.h' | xargs clang-format -i
#)

# Code coverage integration (optional)
if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
    target_compile_options(Option_pricer PRIVATE --coverage)
    target_link_libraries(Option_pricer PRIVATE --coverage)
endif()