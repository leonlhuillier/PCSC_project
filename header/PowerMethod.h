#ifndef POWERMETHOD_H
#define POWERMETHOD_H

#include "Eigenvalue.h"

template<typename Scalar>
class PowerMethod : public Eigenvalue<Scalar> {
public:
    using Matrix = typename Eigenvalue<Scalar>::Matrix;
    using Vector = typename Eigenvalue<Scalar>::Vector;
    // Constructors and Destructor
    PowerMethod();
    PowerMethod(const Matrix& matrix, const Parameters& params);
    virtual ~PowerMethod();

    // Overridden Method
    virtual void solve() override;
};

#endif // POWERMETHOD_H