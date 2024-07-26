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
add_executable(Option_pricer main.cpp src/payoff.cpp src/market_data.cpp
        src/option/options/base_option.cpp
        src/option/options/single_path/base_single_path_option.cpp
        src/option/options/single_path/european_option.cpp
        src/option/options/single_path/digital/digital_option.cpp
        src/option/options/single_path/digital/double_digital_option.cpp
        src/option/options/path_dependent/base_path_dependent_option.cpp
        src/option/options/path_dependent/american_option.cpp
        src/option/options/path_dependent/asian/base_asian_option.cpp
        src/option/options/path_dependent/asian/arithmetic_asian_option.cpp
        src/option/options/path_dependent/asian/geometric_asian_option.cpp
        src/option/options/path_dependent/barrier/base_barrier_option.cpp
        src/option/options/path_dependent/barrier/knock_behavior.cpp
        src/option/options/path_dependent/barrier/double_barrier.cpp
        src/option/options/path_dependent/barrier/single_barrier/base_single_barrier_option.cpp
        src/option/options/path_dependent/barrier/single_barrier/up_single_barrier_option.cpp
        src/option/options/path_dependent/barrier/single_barrier/down_single_barrier_option.cpp

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