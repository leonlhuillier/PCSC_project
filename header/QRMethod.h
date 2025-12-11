#ifndef QRMETHOD_H
#define QRMETHOD_H

#include "Eigenvalue.h"

template<typename Scalar>
class QRMethod : public Eigenvalue<Scalar> {
public:
    using Matrix = typename Eigenvalue<Scalar>::Matrix;
    using Vector = typename Eigenvalue<Scalar>::Vector;
    // Constructors and Destructor
    QRMethod();
    QRMethod(const Matrix& matrix, const Parameters& params);
    virtual ~QRMethod();

    // Overridden Method
    virtual void solve() override;
    Vector getAllEigenvalues() const { return mAllEigenvalues; }
    Matrix getAllEigenvectors() const { return mAllEigenvectors; }
private:
    Vector mAllEigenvalues;    // Stocke toutes les valeurs propres
    Matrix mAllEigenvectors;   // Stocke tous les vecteurs propres (en colonnes)
};


#endif // QRMETHOD_H