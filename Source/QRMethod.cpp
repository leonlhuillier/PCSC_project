#include "QRMethod.h"
#include <Eigen/QR>
#include <Eigen/Eigenvalues>  // Pour EigenSolver

#include <cmath>
#include <iostream>
#include <complex>


//Default Constructor
template<typename Scalar>
QRMethod<Scalar>::QRMethod()
    : Eigenvalue<Scalar>(Matrix::Identity(3, 3), Parameters())
{
}

//Destructor
template<typename Scalar>
QRMethod<Scalar>::~QRMethod() {}

//Constructor
template<typename Scalar>
QRMethod<Scalar>::QRMethod(const Matrix& matrix, const Parameters& params)
    : Eigenvalue<Scalar>(matrix, params) {} // Appelle le constructeur de la classe mère


// Templates to handle real and complex
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
    //Accumulation of Q matrix for the eigenvectors
    Matrix Q_accumulated = Matrix::Identity(n, n);

    this->mConverged = false;
    this->mIterationCount = 0;

    for (this->mIterationCount = 1;
         this->mIterationCount <= this->mMaxIteration;
         ++this->mIterationCount) {
        // 1. QR Decomposition: A_k = Q_k * R_k
        // Use Eigen's Householder QR decomposition
        Eigen::HouseholderQR<Matrix> qr(A);
        Matrix Q = qr.householderQ();

        // Get the upper triangular factor R from the decomposed matrix
        // The template view ensures correct type handling for complex numbers if Scalar is complex.
        Matrix R = qr.matrixQR().template triangularView<Eigen::Upper>();


        // 2. Re-multiplication: A_k+1 = R_k * Q_k
        Matrix A_next = R * Q;

        Q_accumulated = Q_accumulated * Q;

        // 3. Check for convergence: all sub-diagonal elements should approach zero
        // When the matrix becomes sufficiently upper-triangular, eigenvalues appear on the diagonal

        // Find the maximum magnitude of all sub-diagonal elements
        double max_subdiag = 0.0;
        for (int i = 0; i < n - 1; ++i) {
            double val = std::abs(A_next(i + 1, i));  //Sub diagonal element
            if (val > max_subdiag) {
                max_subdiag = val;
            }
        }

        // Check if largest sub-diagonal element is below tolerance
        // std::abs handles the magnitude for both real and complex types
        if (std::abs(max_subdiag) < this->mTolerance) {
            this->mConverged = true;
            A = A_next;  // Store the final quasi-triangular matri
            break;
        }

        // 4. Update for next iteration
        A = A_next;
    }

    // Extract all the eigenvalues of the diagonal
    mAllEigenvalues.resize(n);
    for (int i = 0; i < n; ++i) {
        mAllEigenvalues(i) = A(i, i);
    }

    // Stock the highest eigenvalue
    int max_idx = 0;
    double max_magnitude = std::abs(mAllEigenvalues(0));
    for (int i = 1; i < n; ++i) {
        double mag = std::abs(mAllEigenvalues(i));
        if (mag > max_magnitude) {
            max_magnitude = mag;
            max_idx = i;
        }
    }
    this->mEigenvalue = mAllEigenvalues(max_idx);

    // eigenvectors are the column of Q accumulated
    mAllEigenvectors = Q_accumulated;
    this->mEigenvector = Q_accumulated.col(max_idx);


    if (this->mConverged) {
        std::cout << "QRMethod converged (eigenvalues on diagonal) after " << this->mIterationCount << " iterations." << std::endl;
    } else {
        std::cerr << "QRMethod failed to converge after " << this->mMaxIteration << " iterations." << std::endl;
    }
}

// Explicit instantiations for common types (to ensure code generation)
template class QRMethod<double>;
template class QRMethod<std::complex<double>>;