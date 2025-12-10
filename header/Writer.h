#ifndef WRITER_H
#define WRITER_H

#include <Eigen/Dense>
#include <complex>

using Vector = Eigen::VectorXd;

class Writer {
public:
    // Constructor and Destructor
    Writer();
    virtual ~Writer();

    void setResults(double eigenvalue, const Vector& eigenvector) {
        mEigenvalue = eigenvalue;
        mEigenvector = eigenvector;

    // Pure Virtual Method
    virtual void Write()= 0;

protected:
        double mEigenvalue;
        Vector mEigenvector;
};

#endif // WRITER_H