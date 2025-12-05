cmake_minimum_required(VERSION 3.10)
project(EigenvalueComputation)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/matrix.cpp
    src/power_method.cpp
    src/qr_algorithm.cpp
    src/jacobi_method.cpp
)

# Header files
set(HEADERS
    include/matrix.h
    include/power_method.h
    include/qr_algorithm.h
    include/jacobi_method.h
)

# Main executable
add_executable(eigenvalue_demo src/main.cpp ${SOURCES} ${HEADERS})

# Enable testing
enable_testing()

# Test executable (optional, if you want to add tests later)
add_executable(eigenvalue_tests tests/test_main.cpp ${SOURCES})
add_test(NAME EigenvalueTests COMMAND eigenvalue_tests)
