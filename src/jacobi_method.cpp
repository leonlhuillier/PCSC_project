#include "jacobi_method.h"
#include <cmath>
#include <iostream>
#include <limits>

// Define PI constant for portability (M_PI is not standard)
constexpr double PI = 3.141592653589793;

std::vector<double> JacobiMethod::compute(
    const Matrix& A,
    size_t max_iterations,
    double tolerance
) {
    if (A.getRows() != A.getCols()) {
        throw std::invalid_argument("Matrix must be square for Jacobi Method");
    }
    
    if (!A.isSymmetric()) {
        std::cout << "Warning: Matrix is not symmetric. Jacobi method may not converge properly." << std::endl;
    }
    
    size_t n = A.getRows();
    Matrix Ak = A;
    
    for (size_t iter = 0; iter < max_iterations; ++iter) {
        // Find largest off-diagonal element
        auto [p, q] = findLargestOffDiagonal(Ak);
        
        // Check for convergence
        double off_norm = offDiagonalNorm(Ak);
        if (off_norm < tolerance) {
            std::cout << "Jacobi Method converged in " << iter + 1 << " iterations" << std::endl;
            break;
        }
        
        // Compute Jacobi rotation matrix
        Matrix J = jacobiRotation(Ak, p, q);
        
        // Apply similarity transformation: A_{k+1} = J^T * A_k * J
        Matrix JT = J.transpose();
        Ak = JT * Ak * J;
    }
    
    // Extract eigenvalues from diagonal
    std::vector<double> eigenvalues(n);
    for (size_t i = 0; i < n; ++i) {
        eigenvalues[i] = Ak(i, i);
    }
    
    return eigenvalues;
}

std::pair<size_t, size_t> JacobiMethod::findLargestOffDiagonal(const Matrix& A) {
    size_t n = A.getRows();
    double max_val = 0.0;
    size_t max_i = 0, max_j = 1;
    
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            double val = std::abs(A(i, j));
            if (val > max_val) {
                max_val = val;
                max_i = i;
                max_j = j;
            }
        }
    }
    
    return {max_i, max_j};
}

Matrix JacobiMethod::jacobiRotation(const Matrix& A, size_t p, size_t q) {
    size_t n = A.getRows();
    Matrix J = Matrix::identity(n);
    
    double a_pp = A(p, p);
    double a_qq = A(q, q);
    double a_pq = A(p, q);
    
    // Compute rotation angle
    double theta;
    if (std::abs(a_pp - a_qq) < 1e-10) {
        theta = PI / 4.0;
    } else {
        theta = 0.5 * std::atan2(2.0 * a_pq, a_qq - a_pp);
    }
    
    double c = std::cos(theta);
    double s = std::sin(theta);
    
    // Set rotation matrix elements
    J(p, p) = c;
    J(q, q) = c;
    J(p, q) = s;
    J(q, p) = -s;
    
    return J;
}

double JacobiMethod::offDiagonalNorm(const Matrix& A) {
    size_t n = A.getRows();
    double sum = 0.0;
    
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            sum += A(i, j) * A(i, j);
        }
    }
    
    return std::sqrt(sum);
}
