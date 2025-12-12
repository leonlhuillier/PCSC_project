# PCSC_project

## Requirements:
  - Compiler C++17 or above
  - [CMake](https://cmake.org/download/) version 3.10 or above
    
## Dependency :
  - [Eigen Library](https://libeigen.gitlab.io/?title=Main_Page) imported

## Download the project : 
Copy this into your terminal : git clone https://github.com/leonlhuillier/PCSC_project.git 

## Compile :
Run this in your terminal to compile your project :`./source/main`

## File Composition :
Each file **must** contains each of the following parameters to be calculated :
   - Matrix of real or complex number
   - Method that we want to use
   - Tolerance
   - Maximum Iterations
   - Shift (optional)

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


  

