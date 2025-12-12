# PCSC_project

## Requirements:
  - Compiler C++17 or above
  - [CMake](https://cmake.org/download/) version 3.10 or above
    
## Dependency :
  - [Eigen Library](https://libeigen.gitlab.io/?title=Main_Page) imported

## Download the project : 
Copy this into your terminal : git clone https://github.com/leonlhuillier/PCSC_project.git 

## Compile :
1. In the project click **Build** (icon) 
2. Select target from dropdown menu :
  - `PCSC_project` → Main program
  - `test_reader` → Test file readers
  - `test_powermethod` → Test Power Method
  - `test_ShiftInversepm` → Test Shifted Inverse Power Method
  - `test_QRMethod` → Test QR Method
3. Click **Run** (▶ icon)

## File Composition :
Each file **must** contains each of the following parameters in this specific order to be calculated :
   - Matrix of real or complex number
   - Method that we want to use
   - Tolerance
   - Maximum Iterations
   - Shift (optional)

Here is an example of the content of a file : 
```
4,-1,0
-1,3,-1
0,-1,2
Algorithm,ShiftedInversePowerMethod
Shift,2.5
MaxIterations,1000
Tolerance,1.0E-10
```

## Programm execution :

1- The programm gets the input file which contains all the matrix information, and all the configuration settings such as the method name, the tolerance, the maximum number of iterations or the shift.

2- **You indicate** the type of data contained in the matrix. There is two option, real number or complex number. Regarding the type of data, one method is called to run the computaion.

3- It detect the type of file : CSV or Text file. 

4- It reads the file, gets the matrix and parameters informations.

5- It plots some informations such as matrix size, the matrix itself, the configuration settings.

6- Validation of the parameters, if it fails, stop with message : Invalid   parameters ! 
Else, continue

7- Selction of the method to execute, based on the information contained in the file. It can be :
 - Power Method : calculates the dominant eigenvalue.
 - Shifted Inverse Power Method : aims to an eigenvalue close to the shift ( If the shift is 0, it is the Inverse Power Method).
 - QR Method : calculates all the eigenvalues and associated eigenvectors. 

8- **You chose** the output file type, either CSV or text file. Then, it choses an output path to store the results, with the writer object.

9- The programm creates the object from the method used, calls solve() to calculate the eigenvalues, gets the results and plot a summary of the results onto the console.

10- Write the results in the created file and gives you its path.


## List of Features & Tests

### Features Implemented

####  File Reading System
The project includes a file reading system that support two types of format :

- **CSV file reading** (`.csv` format) implemented in the `CSVReader` class
- **Text file reading** (`.txt`, `.dat` formats) implemented in the `TextFileReader` class
  It detects automatically the filetype based on the end of the file name (eg. “.csv”).

#### Parameter Extraction
Since the algorithms need parameters to compute, the reader class and its daughters extract the parameters in the input file such as:
- Matrix to compute
- Algorithm name
- Tolerance threshold
- Maximum number of iterations
- Shift value (used for Power Method variants)

All parameters are stored in the `Parameter` class .

#### Matrix Support
The program can support:
-  Real matrices
-  Complex Matrices
-  Large dimensions (tested up to 50×50 matrices)

#### Eigenvalue Algorithms
Our project implements an abstract base class `Eigenvalue<Scalar>` that integrates the `Parameters` class to centralize configuration settings like `convergence tolerance, maximum iterations, and shift values`. All algorithms inherit from this class and implement the pure virtual `solve()` method.


| Algorithm | Output |
|-----------|--------|
| **Power Method** | Largest eigenvalue + eigenvector |
| **Shifted Inverse Power Method** | Eigenvalue closest to given shift |
| **QR Algorithm** | All eigenvalues and eigenvectors |

#### User Interface
The program provides an interactive command-line interface where users can:
- Specify the input file path
- Choose between real or complex matrix types
- Select the output file format (`.txt` or `.csv`)

#### Output Format
Results are saved in `results.txt` or `results.csv` containing:
- **Convergence status** (whether the algorithm converged)
- **Number of iterations** required
- **Eigenvalue(s)** computed
- **Eigenvector(s)** computed

---

### Test Suite

The project includes  tests to validate functionality:

| Test File | Purpose |
|-----------|---------|
| `test_reader.cpp` | Tests file reading and parameter extraction |
| `test_powermethod.cpp` | Validates Power Method implementation |
| `test_ShiftInversepm.cpp` | Validates Shifted Inverse Power Method |
| `test_QRMethod.cpp` | Validates QR Algorithm implementation |

It permits us to handle errors more easily in the program, because we can know the source of the problem and fix it. 


# TODOs and Perspective

Our program is a good and simple eigenvalue computation program but it can be more autonomous and performant, and we can improve it further.

### Potential Improvements

- Automatically detect if the matrix is complex or real to avoid asking the user
- Handle more types of files (JSON, XLS, HTML, etc.)
- Compute another algorithm or fix the error if the algorithm doesn't converge
- A spectral plot in the results file. 
- The output can ask to change the tolerance if the algorithm didn't converge 

### Algorithm Limitations

There are some limitations due to the eigenvalue computation algorithms themselves that users should be aware of:

#### Power Method

- Only finds the largest eigenvalue (cannot compute λ₂, λ₃, etc.)
- Slow convergence when |λ₁| ≈ |λ₂| (may require 500+ iterations)
- Fails to converge if two eigenvalues have equal magnitude (e.g., λ₁=5, λ₂=-5)

#### Shifted Inverse Power Method

- Numerically unstable when shift σ ≈ actual eigenvalue
- Fails if shift equals an eigenvalue exactly (singular matrix)
- Requires good initial guess for shift parameter

#### QR Method

- Fast for large eigenvalues (|λ| > 10)
- Very slow for small eigenvalues (|λ| < 1)
- Cannot be applied to large sparse matrices, because of excessive memory requirements

## Use of llms 
As beginners in C++ numerical computing, we occasionally consulted LLMs for guidance on specific technical aspects. 

- Understanding the `<complex>` standard library(e.g., `std::complex<double>`)
-  Usage of `#include <cctype>` 
- Learning Eigen library

### Specific Code generated by llms
- Implementation of the `trim()` method to remove leading and trailing whitespace in `CSVReader.cpp` and `TextFileReader.cpp`
  ```cpp
  std::string trim(const std::string& str) {
      // Removes spaces/tabs from both ends
  
  }

-Extraction of Q and R matrix in `QRMethod.cpp` :         
```// Use Eigen's Householder QR decomposition
Eigen::HouseholderQR<Matrix> qr(A);
Matrix Q = qr.householderQ();



