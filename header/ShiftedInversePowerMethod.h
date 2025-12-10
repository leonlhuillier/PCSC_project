#ifndef SHIFTEDINVERSEPOWERMETHOD_H
#define SHIFTEDINVERSEPOWERMETHOD_H

#include "Eigenvalue.h"

template<typename Scalar>
class ShiftedInversePowerMethod : public Eigenvalue<Scalar> {
public:
    using Matrix = typename Eigenvalue<Scalar>::Matrix;
    using Vector = typename Eigenvalue<Scalar>::Vector;
    // Constructors and Destructor
    ShiftedInversePowerMethod();
    ShiftedInversePowerMethod(const Matrix& matrix, const Parameters& params);
    virtual ~ShiftedInversePowerMethod();

    // Overridden Method
    virtual void solve() override;
};

#endif // SHIFTEDINVERSEPOWERMETHOD_H