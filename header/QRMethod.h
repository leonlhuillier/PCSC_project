#ifndef QRMETHOD_H
#define QRMETHOD_H

#include "Eigenvalue.h"

class QRMethod : public Eigenvalue {
public:
    // Constructors and Destructor
    QRMethod();
    QRMethod(const Eigen::MatrixXd& matrix, int maxIter, double tolerance);
    virtual ~QRMethod();

    // Overridden Method
    virtual void solve() override;
};

#endif // QRMETHOD_H