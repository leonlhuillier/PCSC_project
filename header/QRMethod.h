#ifndef QRMETHOD_H
#define QRMETHOD_H

#include "Eigenvalue.h"

/**
 * \tparam Scalar The underlying numeric type of the matrix elements (e.g., \c double, \c std::complex<double>).
 * \class QRMethod
 * \brief Implements the iterative QR Algorithm for computing all eigenvalues and eigenvectors of a matrix.
 *
 * \details The QR Method is a highly robust and widely used algorithm in numerical linear algebra. It works by
 * iteratively decomposing the matrix $A_k$ into an orthogonal matrix $Q_k$ and an upper triangular matrix $R_k$
 * ($A_k = Q_k R_k$), and then forming the next matrix $A_{k+1} = R_k Q_k$.
 * This transformation is similarity-preserving, meaning $A_{k+1}$ has the same eigenvalues as $A_k$ and $A$.
 * As $k \to \infty$, $A_k$ converges toward a triangular (or block-triangular) matrix whose diagonal elements
 * contain the eigenvalues.
 * * Unlike the Power Method, the QR Method finds all eigenvalues of the matrix simultaneously.
 * \sa Eigenvalue
 */
template<typename Scalar>
class QRMethod : public Eigenvalue<Scalar> {
public:
    /**
     * \brief Type alias for the matrix type used by the solver (e.g., \c Eigen::MatrixXd or \c Eigen::MatrixXcd).
     */
    using Matrix = typename Eigenvalue<Scalar>::Matrix;

    /**
     * \brief Type alias for the vector type used by the solver.
     */
    using Vector = typename Eigenvalue<Scalar>::Vector;

    /**
     * \brief Default constructor. Initializes the solver with default parameters.
     */
    QRMethod();

    /**
     * \brief Parameterized constructor to initialize the solver with the matrix and configuration settings.
     * \details Sets the input matrix and extracts configuration parameters
     * like tolerance and max iterations from the \c Parameters object.
     * \param matrix The input matrix.
     * \param params A structure containing the configuration settings.
     */
    QRMethod(const Matrix& matrix, const Parameters& params);

    /**
     * \brief Destructor for QRMethod.
     */
    virtual ~QRMethod();

    /**
     * \brief Executes the iterative QR Algorithm.
     * \details The core loop performs $A_{k+1} = R_k Q_k$ after $A_k = Q_k R_k$.
     * Upon convergence, the diagonal elements of the transformed matrix $A_k$ are stored in \c mAllEigenvalues.
     * \pre The input matrix must be square.
     * \post The protected members \c mAllEigenvalues and \c mAllEigenvectors will hold the complete set of solutions.
     */
    virtual void solve() override;

    /**
     * \brief Retrieves all computed eigenvalues.
     * \return A vector containing all eigenvalues found during the computation.
     */
    Vector getAllEigenvalues() const { return mAllEigenvalues; }

    /**
     * \brief Retrieves all computed eigenvectors.
     * \return A matrix where each column is an eigenvector corresponding to the eigenvalue at the same index in \c mAllEigenvalues.
     */
    Matrix getAllEigenvectors() const { return mAllEigenvectors; }

private:
    /**
     * \brief Vector storing all computed eigenvalues $\lambda_i$.
     */
    Vector mAllEigenvalues;

    /**
     * \brief Matrix storing all computed eigenvectors $x_i$ as its columns.
     */
    Matrix mAllEigenvectors;
};


#endif // QRMETHOD_H