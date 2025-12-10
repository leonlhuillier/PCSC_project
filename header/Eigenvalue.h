#ifndef EIGENVALUE_H
#define EIGENVALUE_H

#include <Eigen/Dense>
#include <complex>
#include "Parameters.h"

template<typename Scalar>
class Eigenvalue {
public:
    using Matrix = Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>;
    using Vector = Eigen::Matrix<Scalar, Eigen::Dynamic, 1>;
    using RealScalar = typename Eigen::NumTraits<Scalar>::Real;

    // Constructors and Destructor
    Eigenvalue(const Matrix& matrix, const Parameters& params);
    virtual ~Eigenvalue();

    // Public Methods
    virtual void solve() = 0;
    void setTolerance(double tolerance);
    void setMatrix(const Matrix& matrix);
    void setMaxIteration(int maxIteration);
    bool hasConverged() const;
    Scalar getEigenvalue() const;
    Vector getEigenvector() const;
    double getTolerance() const;
    int getMaxIterations() const;
    int getIterationCount() const;
    bool IsInvertible() const;


protected:
    Matrix mMatrix;
    Vector mEigenvector;
    Scalar mEigenvalue;
    Scalar mShift;
    int mMaxIteration;
    double mTolerance;
    bool mConverged;
    int mIterationCount;
};

using EigenvalueReal = Eigenvalue<double>;
using EigenvalueComplex = Eigenvalue<std::complex<double>>;

#endif // EIGENVALUE_H
