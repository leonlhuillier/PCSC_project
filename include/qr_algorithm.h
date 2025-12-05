#ifndef QR_ALGORITHM_H
#define QR_ALGORITHM_H

#include "matrix.h"
#include <vector>
#include <utility>

/**
 * QR Algorithm for computing all eigenvalues of a matrix
 * 
 * This method repeatedly performs QR decomposition and multiplies
 * the factors in reverse order to converge to a triangular matrix
 * whose diagonal contains the eigenvalues.
 */
class QRAlgorithm {
public:
    /**
     * Compute all eigenvalues using the QR algorithm
     * 
     * @param A The input matrix (should be square)
     * @param max_iterations Maximum number of iterations
     * @param tolerance Convergence tolerance
     * @return A vector containing all eigenvalues
     */
    static std::vector<double> compute(
        const Matrix& A,
        size_t max_iterations = 1000,
        double tolerance = 1e-6
    );

private:
    /**
     * Perform QR decomposition using Gram-Schmidt process
     * 
     * @param A The input matrix
     * @return A pair of matrices (Q, R) where A = Q*R
     */
    static std::pair<Matrix, Matrix> qrDecomposition(const Matrix& A);
};

#endif // QR_ALGORITHM_H
