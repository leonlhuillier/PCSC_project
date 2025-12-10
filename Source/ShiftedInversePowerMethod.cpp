#include "ShiftedInversePowerMethod.h"
#include <Eigen/LU> // Required for solving the linear system
#include <cmath>
#include <iostream>
#include <complex>


//Default Constructor
template<typename Scalar>
ShiftedInversePowerMethod<Scalar>::ShiftedInversePowerMethod()
    : Eigenvalue<Scalar>(Matrix::Identity(3, 3), Parameters())
{}

//Destructor
template<typename Scalar>
ShiftedInversePowerMethod<Scalar>::~ShiftedInversePowerMethod(){}

//Constructor
template<typename Scalar>
ShiftedInversePowerMethod<Scalar>::ShiftedInversePowerMethod(const Matrix& matrix, const Parameters& params)
    : Eigenvalue<Scalar>(matrix, params) {} // Appelle le constructeur de la classe mère


template<typename Scalar>
void ShiftedInversePowerMethod<Scalar>::solve() {
    // Define aliases for the types inherited from the base class
    using Matrix = typename Eigenvalue<Scalar>::Matrix;
    using Vector = typename Eigenvalue<Scalar>::Vector;

    // 1. Calculate the shifted matrix B = A - mu*I
    // The shift (mu) is mShift. It must be cast to Scalar (for complex types).
    Matrix B = this->mMatrix - this->mShift * Matrix::Identity(this->mMatrix.rows(), this->mMatrix.cols());

    // 2. Pre-compute the LU decomposition of B (for efficient solving of B*y = x)
    // PartialPivLU is used for solving linear systems Ax=b
    Eigen::PartialPivLU<Matrix> lu_of_B(B);

    // Check if the shifted matrix is invertible (i.e., if mShift is an exact eigenvalue)
    Scalar det = lu_of_B.determinant();
    const double epsilon = 1e-10;
    if (std::abs(det) < epsilon) {
        std::cerr << "The matrix (A - mu*I) is singular (shift is likely an exact eigenvalue). Choose a different shift mu." << std::endl;
        return; // Exit the solve function immediately
    }

    Vector x_k = this->mEigenvector; // Current vector (x_k)
    Vector x_k_plus_1;              // Next vector (y_k+1)
    Scalar mu_prime_k = 0.0;        // Previous dominant eigenvalue of B_inverse

    this->mConverged = false;
    this->mIterationCount = 0;

    for (this->mIterationCount = 1;
         this->mIterationCount <= this->mMaxIteration;
         ++this->mIterationCount)
    {

        // 1. Solve the system: B * x_k+1 = x_k
        // This is the core Inverse Power Iteration step.
        x_k_plus_1 = lu_of_B.solve(x_k);

        // 2. Calculate the new dominant eigenvalue of B_inverse (mu_prime)
        // This value is 1 / (lambda_A - mu).
        Eigen::Index max_idx;
        x_k_plus_1.cwiseAbs().maxCoeff(&max_idx);

        Scalar mu_prime_k_plus_1 = x_k_plus_1(max_idx) / x_k(max_idx);

        // 3. Normalize the vector
        x_k_plus_1.normalize();

        // 4. Transform back to the eigenvalue of A: lambda_A = mu + 1/mu_prime
        Scalar lambda_k_plus_1 = static_cast<Scalar>(this->mShift) + (Scalar(1.0) / mu_prime_k_plus_1);

        // 5. Check for convergence based on the inverse eigenvalue (mu_prime)
        // This is typically more stable than checking lambda_A directly.
        if (std::abs(mu_prime_k_plus_1 - mu_prime_k) < this->mTolerance) {
            this->mConverged = true;
            this->mEigenvalue = lambda_k_plus_1;
            this->mEigenvector = x_k_plus_1;
            break;
        }

        // 6. Update for next iteration
        x_k = x_k_plus_1;
        mu_prime_k = mu_prime_k_plus_1;
    }

    if (!this->mConverged) {
        std::cerr << "ShiftedInversePowerMethod failed to converge after " << this->mMaxIteration << " iterations." << std::endl;
        // Calculate the final eigenvalue result
        this->mEigenvalue = static_cast<Scalar>(this->mShift) + (Scalar(1.0) / mu_prime_k);
        this->mEigenvector = x_k;
    }
}

// Explicit instantiations for common types (as discussed in Eigenvalue.cpp)
template class ShiftedInversePowerMethod<double>;
template class ShiftedInversePowerMethod<std::complex<double>>;