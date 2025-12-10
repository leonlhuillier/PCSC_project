#include "PowerMethod.h"
#include <cmath>
#include <iostream>
#include <complex>

// The PowerMethod class must be templated to work with different Scalar types
template<typename Scalar>
void PowerMethod<Scalar>::solve() {
    // Define aliases for the types inherited from the base class
    using Vector = typename Eigenvalue<Scalar>::Vector;

    // This is handled in the base class constructor (mEigenvector is randomized and normalized)
    Vector b_k = this->mEigenvector;

    Vector b_k1;
    Scalar lambda_k = 0.0; // Previous eigenvalue approximation

    this->mConverged = false;
    this->mIterationCount = 0;

    for (this->mIterationCount = 1;
         this->mIterationCount <= this->mMaxIteration;
         ++this->mIterationCount)
    {
        // calculate the matrix-by-vector product Ab
        b_k1 = this->mMatrix * b_k;

        // Find the index of the largest component (in absolute value) in b_k1
        Eigen::Index max_idx;
        b_k1.cwiseAbs().maxCoeff(&max_idx);  // LLM

        // Calculate the new eigenvalue approximation (Ratio of components)
        Scalar lambda_k_plus_1 = b_k1(max_idx) / b_k(max_idx);

        // re normalize the vector
        b_k = b_k1.normalized();
        // std::abs handles the magnitude for both real and complex types
        if (std::abs(lambda_k_plus_1 - lambda_k) < this->mTolerance) {
            this->mConverged = true;
            this->mEigenvalue = lambda_k_plus_1;
            this->mEigenvector = b_k; // b_k is the normalized vector
            break;
        }

        // Update lambda for the next iteration
        lambda_k = lambda_k_plus_1;
    }

    // If the loop finished without converging, save the last result
    if (!this->mConverged) {
        std::cerr << "PowerMethod failed to converge after " << this->mMaxIteration << " iterations." << std::endl;
        this->mEigenvalue = lambda_k;
        this->mEigenvector = b_k;
    }
}

// Ensure the common types are explicitly instantiated
template class PowerMethod<double>;
template class PowerMethod<std::complex<double>>;