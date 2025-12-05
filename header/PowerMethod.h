#ifndef POWERMETHOD_H
#define POWERMETHOD_H

#include "Eigenvalue.h"

class PowerMethod : public Eigenvalue {
public:
    // Constructors and Destructor
    PowerMethod(); [cite_start]
    PowerMethod(const Eigen::MatrixXd& matrix, int maxIter, double tolerance);
    virtual ~PowerMethod();

    // Overridden Method
    virtual void solve() override;
};

#endif // POWERMETHOD_H