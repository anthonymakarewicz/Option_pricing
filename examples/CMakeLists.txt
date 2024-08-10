find_package(Boost REQUIRED COMPONENTS random)

if (Boost_FOUND)
    message(STATUS "Boost found: ${Boost_VERSION}")
else()
    message(FATAL_ERROR "Boost not found!")
endif()

add_executable(sobol generate_sobol.cpp
        generate_sobol.cpp)

target_link_libraries(sobol Boost::random)

set_target_properties(sobol PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/examples)
