# Eigenvalue Computation Project

A C++ project for computing eigenvalues using different numerical methods. This project is designed for CLion and demonstrates three distinct algorithms for eigenvalue computation.

## Overview

This project implements three different methods for computing eigenvalues of matrices:

1. **Power Method**: Computes the dominant (largest magnitude) eigenvalue and its corresponding eigenvector
2. **QR Algorithm**: Computes all eigenvalues of a square matrix using iterative QR decomposition
3. **Jacobi Method**: Computes all eigenvalues of a symmetric matrix using iterative Givens rotations

## Project Structure

```
PCSC_project/
├── CMakeLists.txt          # CMake configuration file
├── README.md               # This file
├── .gitignore             # Git ignore file
├── include/               # Header files
│   ├── matrix.h           # Matrix class and utilities
│   ├── power_method.h     # Power Method interface
│   ├── qr_algorithm.h     # QR Algorithm interface
│   └── jacobi_method.h    # Jacobi Method interface
├── src/                   # Source files
│   ├── matrix.cpp         # Matrix implementation
│   ├── power_method.cpp   # Power Method implementation
│   ├── qr_algorithm.cpp   # QR Algorithm implementation
│   ├── jacobi_method.cpp  # Jacobi Method implementation
│   └── main.cpp           # Demo program
└── tests/                 # Test files
    └── test_main.cpp      # Unit tests
```

## Building the Project

### Prerequisites

- CMake 3.10 or higher
- C++17 compatible compiler (GCC, Clang, or MSVC)
- CLion IDE (recommended) or any CMake-compatible build system

### Build Instructions

#### Using CLion

1. Open CLion
2. Select "Open" and navigate to the project directory
3. CLion will automatically detect CMakeLists.txt and configure the project
4. Click the "Build" button (hammer icon) or press Ctrl+F9 (Cmd+F9 on Mac)

#### Using Command Line

```bash
# Create build directory
mkdir build
cd build

# Configure with CMake
cmake ..

# Build the project
make

# Run the demo program
./eigenvalue_demo

# Run the tests
./eigenvalue_tests
```

## Usage

### Running the Demo

After building, run the `eigenvalue_demo` executable to see demonstrations of all three methods:

```bash
./eigenvalue_demo
```

This will display:
- Individual demonstrations of each method
- Convergence information
- Computed eigenvalues and eigenvectors
- A comparison of all three methods on the same matrix

### Using in Your Code

```cpp
#include "matrix.h"
#include "power_method.h"
#include "qr_algorithm.h"
#include "jacobi_method.h"

// Create a matrix
Matrix A({
    {4.0, 1.0, 2.0},
    {1.0, 3.0, 1.0},
    {2.0, 1.0, 5.0}
});

// Use Power Method
auto [eigenvalue, eigenvector] = PowerMethod::compute(A);

// Use QR Algorithm
std::vector<double> eigenvalues_qr = QRAlgorithm::compute(A);

// Use Jacobi Method (for symmetric matrices)
std::vector<double> eigenvalues_jacobi = JacobiMethod::compute(A);
```

## Methods Description

### 1. Power Method

**Best for**: Finding the dominant eigenvalue quickly

The Power Method iteratively multiplies a matrix by a vector to converge to the eigenvector corresponding to the largest eigenvalue (in magnitude).

**Advantages**:
- Simple and fast
- Low memory usage
- Good for sparse matrices

**Limitations**:
- Only finds one eigenvalue (the dominant one)
- Requires the dominant eigenvalue to be unique

### 2. QR Algorithm

**Best for**: Finding all eigenvalues of any square matrix

The QR Algorithm repeatedly performs QR decomposition (A = QR) and multiplies the factors in reverse order (A' = RQ) to converge to a triangular matrix whose diagonal contains the eigenvalues.

**Advantages**:
- Finds all eigenvalues
- Works for any square matrix
- Numerically stable

**Limitations**:
- More computationally expensive than Power Method
- May converge slowly for matrices with close eigenvalues

### 3. Jacobi Method

**Best for**: Symmetric matrices

The Jacobi Method iteratively applies Givens rotations to eliminate off-diagonal elements, converging to a diagonal matrix whose entries are the eigenvalues.

**Advantages**:
- Very accurate for symmetric matrices
- Simple to implement
- Parallel-friendly

**Limitations**:
- Only works for symmetric matrices
- Can be slow for large matrices

## Testing

Run the test suite to verify the implementations:

```bash
./eigenvalue_tests
```

The test suite includes:
- Matrix construction and basic operations
- Power Method convergence tests
- QR Algorithm accuracy tests
- Jacobi Method tests on symmetric matrices
- Matrix symmetry detection

## Contributing

Feel free to contribute by:
- Adding more eigenvalue computation methods
- Improving performance
- Adding more comprehensive tests
- Enhancing documentation

## License

This project is provided as-is for educational purposes.