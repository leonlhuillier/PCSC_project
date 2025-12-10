#ifndef SHIFTEDINVERSEPOWERMETHOD_H
#define SHIFTEDINVERSEPOWERMETHOD_H

#include "Eigenvalue.h"

template<typename Scalar>
class ShiftedInversePowerMethod : public Eigenvalue<Scalar> {
public:
    // Constructors and Destructor
    ShiftedInversePowerMethod();
    ShiftedInversePowerMethod(const Eigen::MatrixXd& matrix, int maxIter, double tolerance);
    virtual ~ShiftedInversePowerMethod();

    // Overridden Method
    virtual void solve() override;
};

#endif // SHIFTEDINVERSEPOWERMETHOD_H