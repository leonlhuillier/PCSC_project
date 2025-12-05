#ifndef JACOBI_METHOD_H
#define JACOBI_METHOD_H

#include "matrix.h"
#include <vector>
#include <utility>

/**
 * Jacobi Method for computing eigenvalues of a symmetric matrix
 * 
 * This method iteratively applies Givens rotations to eliminate
 * off-diagonal elements, converging to a diagonal matrix whose
 * entries are the eigenvalues.
 */
class JacobiMethod {
public:
    /**
     * Compute all eigenvalues using the Jacobi method
     * 
     * @param A The input matrix (must be symmetric)
     * @param max_iterations Maximum number of iterations
     * @param tolerance Convergence tolerance
     * @return A vector containing all eigenvalues
     */
    static std::vector<double> compute(
        const Matrix& A,
        size_t max_iterations = 1000,
        double tolerance = 1e-9
    );

private:
    /**
     * Find the largest off-diagonal element
     * 
     * @param A The input matrix
     * @return A pair containing the indices (i, j) of the largest element
     */
    static std::pair<size_t, size_t> findLargestOffDiagonal(const Matrix& A);
    
    /**
     * Compute the Jacobi rotation matrix
     * 
     * @param A The input matrix
     * @param p Row index
     * @param q Column index
     * @return The rotation matrix
     */
    static Matrix jacobiRotation(const Matrix& A, size_t p, size_t q);
    
    /**
     * Compute the sum of squares of off-diagonal elements
     * 
     * @param A The input matrix
     * @return The sum of squares
     */
    static double offDiagonalNorm(const Matrix& A);
};

#endif // JACOBI_METHOD_H
