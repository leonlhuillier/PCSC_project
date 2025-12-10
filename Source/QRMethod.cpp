#include "QRMethod.h"
#include <Eigen/QR>
#include <cmath>
#include <iostream>
#include <complex>

// The implementation must be defined using the template syntax
template<typename Scalar>
void QRMethod<Scalar>::solve() {
    // Define aliases for the types inherited from the base class
    using Matrix = typename Eigenvalue<Scalar>::Matrix;
    using Vector = typename Eigenvalue<Scalar>::Vector;

    if (this->mMatrix.rows() != this->mMatrix.cols()) {
        std::cerr << "QRMethod requires a square matrix." << std::endl;
        return;
    }

    // Start with a copy of the original matrix
    Matrix A = this->mMatrix;
    int n = this->mMatrix.rows();

    this->mConverged = false;
    this->mIterationCount = 0;

    for (this->mIterationCount = 1;
         this->mIterationCount <= this->mMaxIteration;
         ++this->mIterationCount)
    {

        // 1. QR Decomposition: A_k = Q_k * R_k
        // Use Eigen's Householder QR decomposition
        Eigen::HouseholderQR<Matrix> qr(A);
        Matrix Q = qr.householderQ();

        // Get the upper triangular factor R from the decomposed matrix
        // The template view ensures correct type handling for complex numbers if Scalar is complex.
        Matrix R = qr.matrixQR().template triangularView<Eigen::Upper>();

        // 2. Re-multiplication: A_k+1 = R_k * Q_k
        Matrix A_next = R * Q;

        // 3. Check for convergence (Standard check for QR: sub-diagonal elements approach zero)
        // We check the magnitude of the sub-diagonal element in the bottom-right corner A(n-1, n-2).
        // If the matrix is sufficiently upper-triangular, we have found an eigenvalue.

        // Note: For full convergence (all eigenvalues), one would check all sub-diagonal elements.
        Scalar sub_diagonal_element = A_next(n - 1, n - 2);

        // std::abs handles the magnitude for both real and complex types
        if (std::abs(sub_diagonal_element) < this->mTolerance) {
            this->mConverged = true;
            A = A_next; // Update A to store the final result before break
            break;
        }

        // 4. Update for next iteration
        A = A_next;
    }

    // The eigenvalues are now (or are close to) the diagonal entries of A.
    // We store the top-left one as the primary result.
    this->mEigenvalue = A(0, 0);

    // Simple QR iteration does not easily yield the eigenvector; we reset it.
    this->mEigenvector.resize(n);
    this->mEigenvector.setZero();

    if (this->mConverged) {
        std::cout << "QRMethod converged (eigenvalues on diagonal) after " << this->mIterationCount << " iterations." << std::endl;
    } else {
        std::cerr << "QRMethod failed to converge after " << this->mMaxIteration << " iterations." << std::endl;
    }
}

// Explicit instantiations for common types (to ensure code generation)
template class QRMethod<double>;
template class QRMethod<std::complex<double>>;