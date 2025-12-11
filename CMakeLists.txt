cmake_minimum_required(VERSION 3.10)
project(PCSC_project)

# Standard C++ setting
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ========================================
# Fetch Eigen from GitLab
# ========================================
include(FetchContent)
FetchContent_Declare(
        Eigen
        GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
        GIT_TAG 3.4.0
        GIT_SHALLOW TRUE
)
set(EIGEN_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(BUILD_TESTING OFF CACHE BOOL "" FORCE)
set(EIGEN_BUILD_PKGCONFIG OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(Eigen)

# ========================================
# Add directories for headers
# ========================================
include_directories(${CMAKE_SOURCE_DIR}/header)


set(COMMON_SOURCES
        Source/Parameters.cpp
        Source/Eigenvalue.cpp
        Source/PowerMethod.cpp
        Source/ShiftedInversePowerMethod.cpp
        Source/QRMethod.cpp
        Source/Reader.cpp
        Source/CSVReader.cpp
        Source/TextFileReader.cpp
        Source/Writer.cpp
)

# ========================================
# TEST EXECUTABLES
# ========================================

# Test Reader
add_executable(test_reader
        Source/test_reader.cpp
        Source/TextFileReader.cpp
        Source/CSVReader.cpp
        Source/Reader.cpp
        Source/Parameters.cpp
)
target_link_libraries(test_reader PRIVATE Eigen3::Eigen)

# Test Power Method
add_executable(test_powermethod
        Source/test_powermethod.cpp
        ${COMMON_SOURCES}
)
target_link_libraries(test_powermethod PRIVATE Eigen3::Eigen)

# Test Shifted Inverse Power Method
add_executable(test_ShiftInversepm
        Source/test_ShiftInversepm.cpp
        ${COMMON_SOURCES}
)
target_link_libraries(test_ShiftInversepm PRIVATE Eigen3::Eigen)

# Test QR Method
add_executable(test_QRMethod
        Source/test_QRMethod.cpp
        ${COMMON_SOURCES}
)
target_link_libraries(test_QRMethod PRIVATE Eigen3::Eigen)

# ========================================
# MAIN EXECUTABLE
# ========================================
add_executable(PCSC_project
        main.cpp
        ${COMMON_SOURCES}
)
target_link_libraries(PCSC_project PRIVATE Eigen3::Eigen)
