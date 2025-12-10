#ifndef QRMETHOD_H
#define QRMETHOD_H

#include "Eigenvalue.h"

template<typename Scalar>
class QRMethod : public Eigenvalue<Scalar> {
public:
    // Constructors and Destructor
    QRMethod();
    QRMethod(const Eigen::MatrixXd& matrix, int maxIter, double tolerance);
    virtual ~QRMethod();

    // Overridden Method
    virtual void solve() override;
};

#endif // QRMETHOD_H