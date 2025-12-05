#ifndef POWER_METHOD_H
#define POWER_METHOD_H

#include "matrix.h"
#include <utility>

/**
 * Power Method for computing the dominant eigenvalue and eigenvector
 * 
 * This method iteratively multiplies a matrix by a vector to converge
 * to the eigenvector corresponding to the largest eigenvalue (in magnitude).
 */
class PowerMethod {
public:
    /**
     * Compute the dominant eigenvalue and eigenvector
     * 
     * @param A The input matrix
     * @param max_iterations Maximum number of iterations
     * @param tolerance Convergence tolerance
     * @return A pair containing the eigenvalue and eigenvector
     */
    static std::pair<double, std::vector<double>> compute(
        const Matrix& A,
        size_t max_iterations = 1000,
        double tolerance = 1e-6
    );
};

#endif // POWER_METHOD_H
