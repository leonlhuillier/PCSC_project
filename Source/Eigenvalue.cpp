#include "Eigenvalue.h"
#include <Eigen/LU> // Required for Eigen::FullPivLU
#include <cmath>
#include <iostream>
#include <complex>
// Template Implementation
template class Eigenvalue<double>;
template class Eigenvalue<std::complex<double>>;


// Constructor
// Template to work with different Scalar types particulary for matrices
template<typename Scalar>
Eigenvalue<Scalar>::Eigenvalue(const Matrix& matrix, const Parameters& params)
    : mMatrix(matrix),
      mMaxIteration(params.getMaxIterations()),
      mTolerance(params.getTolerance()),
      mConverged(false),
      mIterationCount(0) {

    if (mMatrix.rows() != mMatrix.cols()) {
        std::cerr << "Error: Matrix must be square to be invertible." << std::endl;
    }

    // Initialize eigenvector as a random normalized vector
    mEigenvector.resize(mMatrix.cols());
    mEigenvector.setRandom();
    mEigenvector.normalize();
    mEigenvalue = Scalar(0.0);
}

// Destructor
template<typename Scalar>
Eigenvalue<Scalar>::~Eigenvalue() {}

// Setters
template<typename Scalar>
void Eigenvalue<Scalar>::setTolerance(double tolerance) {
    mTolerance = tolerance;
}

template<typename Scalar>
void Eigenvalue<Scalar>::setMatrix(const Matrix& matrix) {
    mMatrix = matrix;
}

template<typename Scalar>
void Eigenvalue<Scalar>::setMaxIteration(int maxIteration) {
    mMaxIteration = maxIteration;
}

// Getters
template<typename T>
bool Eigenvalue<T>::hasConverged() const {
    return mConverged;
}

template<typename Scalar>
Scalar Eigenvalue<Scalar>::getEigenvalue() const {
    return mEigenvalue;
}

template<typename Scalar>
typename Eigenvalue<Scalar>::Vector Eigenvalue<Scalar>::getEigenvector() const {
    return mEigenvector;
}

template<typename Scalar>
double Eigenvalue<Scalar>::getTolerance() const {
    return mTolerance;
}

template<typename Scalar>
int Eigenvalue<Scalar>::getMaxIterations() const {
    return mMaxIteration;
}

template<typename Scalar>
int Eigenvalue<Scalar>::getIterationCount() const {
    return mIterationCount;
}

template<typename Scalar>
bool Eigenvalue<Scalar>::IsInvertible() const {
    if (mMatrix.rows() != mMatrix.cols()) {
        std::cerr << "Error: Matrix must be square to be invertible." << std::endl;
        return false;
    }
    Eigen::FullPivLU<Matrix> lu_decomp(mMatrix);
    Scalar det = lu_decomp.determinant();

    // Define a small tolerance (epsilon) for comparison.
    // We use a safe value like 1e-10, close to machine precision for doubles.
    const double epsilon = 1e-10;

    // The matrix is invertible if the magnitude of the determinant is greater than epsilon.
    // std::abs handles the magnitude for both real (double) and complex types.
    if (std::abs(det) > epsilon) {
        return true;
    } else {
        std::cerr << "Warning: Matrix is detected as numerically singular (|Det| <= " << epsilon << ")." << std::endl;
        return false;
    }
}

