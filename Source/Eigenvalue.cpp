//
// Created by 32484 on 05-12-25.
//
#include "Eigenvalue.h"
#include <iostream>

#include "Parameters.h"
#include "blas/common.h"


template<typename Scalar>
Eigenvalue<Scalar>::Eigenvalue(const Matrix& matrix, const Parameters& params)
    : mMatrix(matrix),
      mEigenvalue(Scalar(0)),
      mMaxIteration(params.getMaxIterations()),
      mTolerance(params.getTolerance()),
      mConverged(false),
      mIterationCount(0)
{
    if (matrix.rows() != matrix.cols()) {
        throw std::runtime_error("The matrix is not square");
    }
    if (matrix.rows() == 0) {
        throw std::runtime_error("The Matrix is empty");
    }

    mEigenvector = Vector::Random(matrix.rows());
    mEigenvector.normalize();

}

template<typename Scalar>
Eigenvalue<Scalar>::~Eigenvalue() {}

template<typename Scalar>
void Eigenvalue<Scalar>::setTolerance(double tolerance) {
    mTolerance = tolerance;
}

template<typename Scalar>
void Eigenvalue<Scalar>::setMaxIteration(int maxIteration) {
    mMaxIteration = maxIteration;
}

template<typename Scalar>
void Eigenvalue<Scalar>::setMatrix(const Matrix& matrix) {
    mMatrix = matrix;
}

template<typename Scalar>
bool Eigenvalue<Scalar>::hasConverged() const {
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
int Eigenvalue<Scalar>::getIterationCount() const {
    return mIterationCount;
}

template<typename Scalar>
double Eigenvalue<Scalar>::getTolerance() const {
    return mTolerance;
}

template<typename Scalar>
int Eigenvalue<Scalar>::getMaxIteration() const {
    return mMaxIteration;
}

template class Eigenvalue<double>;
template class Eigenvalue<std::complex<double>>;