#include "qr_algorithm.h"
#include <cmath>
#include <iostream>

std::vector<double> QRAlgorithm::compute(
    const Matrix& A,
    size_t max_iterations,
    double tolerance
) {
    if (A.getRows() != A.getCols()) {
        throw std::invalid_argument("Matrix must be square for QR Algorithm");
    }
    
    Matrix Ak = A;
    size_t n = A.getRows();
    
    for (size_t iter = 0; iter < max_iterations; ++iter) {
        // Perform QR decomposition
        auto [Q, R] = qrDecomposition(Ak);
        
        // Compute A_{k+1} = R * Q
        Matrix Ak_next = R * Q;
        
        // Check for convergence (off-diagonal elements should be near zero)
        double off_diag_sum = 0.0;
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                if (i != j) {
                    off_diag_sum += std::abs(Ak_next(i, j));
                }
            }
        }
        
        if (off_diag_sum < tolerance) {
            std::cout << "QR Algorithm converged in " << iter + 1 << " iterations" << std::endl;
            Ak = Ak_next;
            break;
        }
        
        Ak = Ak_next;
    }
    
    // Extract eigenvalues from diagonal
    std::vector<double> eigenvalues(n);
    for (size_t i = 0; i < n; ++i) {
        eigenvalues[i] = Ak(i, i);
    }
    
    return eigenvalues;
}

std::pair<Matrix, Matrix> QRAlgorithm::qrDecomposition(const Matrix& A) {
    size_t m = A.getRows();
    size_t n = A.getCols();
    
    Matrix Q(m, n);
    Matrix R(n, n);
    
    // Gram-Schmidt process
    for (size_t j = 0; j < n; ++j) {
        // Extract column j of A
        std::vector<double> a_j(m);
        for (size_t i = 0; i < m; ++i) {
            a_j[i] = A(i, j);
        }
        
        // Orthogonalize against previous columns
        std::vector<double> q_j = a_j;
        for (size_t k = 0; k < j; ++k) {
            // Extract column k of Q
            std::vector<double> q_k(m);
            for (size_t i = 0; i < m; ++i) {
                q_k[i] = Q(i, k);
            }
            
            // Compute R(k, j) = q_k^T * a_j
            double r_kj = dotProduct(q_k, a_j);
            R(k, j) = r_kj;
            
            // Subtract projection
            for (size_t i = 0; i < m; ++i) {
                q_j[i] -= r_kj * q_k[i];
            }
        }
        
        // Normalize
        double norm = vectorNorm(q_j);
        R(j, j) = norm;
        
        if (norm > 1e-10) {
            for (size_t i = 0; i < m; ++i) {
                Q(i, j) = q_j[i] / norm;
            }
        } else {
            // Handle near-zero column
            for (size_t i = 0; i < m; ++i) {
                Q(i, j) = 0.0;
            }
        }
    }
    
    return {Q, R};
}
