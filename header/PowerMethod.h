#ifndef POWERMETHOD_H
#define POWERMETHOD_H

#include "Eigenvalue.h"

template<typename Scalar>
class PowerMethod : public Eigenvalue<Scalar> {
public:
    // Constructors and Destructor
    PowerMethod();
    PowerMethod(const Eigen::MatrixXd& matrix, int maxIter, double tolerance);
    virtual ~PowerMethod();

    // Overridden Method
    virtual void solve() override;
};

#endif // POWERMETHOD_H