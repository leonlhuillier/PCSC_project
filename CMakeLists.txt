cmake_minimum_required(VERSION 3.10)
project(PCSC_project)

# Standard C++ setting
set(CMAKE_CXX_STANDARD 17)

# Find and include Eigen3
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

# Add directories for headers and sources
include_directories(include)

# Define source files
set(SOURCE_FILES
        Source/Eigenvalue.cpp
        Source/PowerMethod.cpp
        Source/ShiftedInversePowerMethod.cpp
        Source/QRMethod.cpp
        Source/Reader.cpp
        Source/CSVReader.cpp
        Source/TextFileReader.cpp
        Source/Writer.cpp
        Source/FileWriter.cpp
        Source/ConsoleWriter.cpp
        Source/PlotWriter.cpp
        main.cpp
)

# Create the executable
add_executable(PCSC_project ${SOURCE_FILES})