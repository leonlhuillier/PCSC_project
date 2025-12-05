#include "power_method.h"
#include <cmath>
#include <iostream>

std::pair<double, std::vector<double>> PowerMethod::compute(
    const Matrix& A,
    size_t max_iterations,
    double tolerance
) {
    if (A.getRows() != A.getCols()) {
        throw std::invalid_argument("Matrix must be square for Power Method");
    }
    
    size_t n = A.getRows();
    
    // Initialize with a random vector
    std::vector<double> v(n, 1.0);
    v = normalizeVector(v);
    
    double eigenvalue = 0.0;
    double prev_eigenvalue = 0.0;
    
    for (size_t iter = 0; iter < max_iterations; ++iter) {
        // Multiply A * v
        std::vector<double> Av = A * v;
        
        // Compute eigenvalue (Rayleigh quotient)
        eigenvalue = dotProduct(v, Av);
        
        // Normalize for next iteration
        v = normalizeVector(Av);
        
        // Check convergence
        if (iter > 0 && std::abs(eigenvalue - prev_eigenvalue) < tolerance) {
            std::cout << "Power Method converged in " << iter + 1 << " iterations" << std::endl;
            break;
        }
        
        prev_eigenvalue = eigenvalue;
    }
    
    return {eigenvalue, v};
}
