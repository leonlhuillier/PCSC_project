#ifndef POWERMETHOD_H
#define POWERMETHOD_H

#include "Eigenvalue.h"

/**
 * \tparam Scalar The underlying numeric type of the matrix elements (e.g., \c double, \c std::complex<double>).
 * \class PowerMethod
 * \brief Implements the iterative Power Method algorithm to find the dominant eigenvalue and its corresponding eigenvector.
 *
 * \details The Power Method is an iterative numerical technique designed to find the eigenvalue with the largest
 * absolute value and its corresponding eigenvector. It works by repeatedly
 * applying the matrix $A$ to an arbitrary initial vector $x_0$:
 * $x_{k+1} = A x_k$.
 * The normalization factor eventually converges to the dominant eigenvalue $\lambda_1$.
 * The method is most effective when the dominant eigenvalue is well-separated from the others.
 * \sa Eigenvalue
 * \sa ShiftedInversePowerMethod
 */
template<typename Scalar>
class PowerMethod : public Eigenvalue<Scalar> {
public:
    /**
     * \brief Type alias for the matrix type used by the solver (e.g., \c Eigen::MatrixXd).
     */
    using Matrix = typename Eigenvalue<Scalar>::Matrix;

    /**
     * \brief Type alias for the vector type used by the solver (e.g., \c Eigen::VectorXd).
     */
    using Vector = typename Eigenvalue<Scalar>::Vector;

    /**
     * \brief Default constructor. Initializes the solver with default parameters.
     */
    PowerMethod();

    /**
     * \brief Parameterized constructor to initialize the solver with the matrix and configuration settings.
     * \details Sets the input matrix and extracts configuration parameters
     * like tolerance and max iterations from the \c Parameters object.
     * \param matrix The input matrix for which the dominant eigenvalue is sought.
     * \param params A structure containing the configuration settings.
     */
    PowerMethod(const Matrix& matrix, const Parameters& params);

    /**
     * \brief Destructor for PowerMethod.
     */
    virtual ~PowerMethod();


    /**
     * \brief Executes the iterative Power Method algorithm.
     * \details The iterative process is:
     * 1. Choose an initial vector $x_0$.
     * 2. Iterate: Calculate $y_{k+1} = A x_k$.
     * 3. Normalize: $x_{k+1} = y_{k+1} / \|y_{k+1}\|$.
     * 4. Estimate $\lambda_{k+1}$ using the Rayleigh quotient.
     * The loop continues until the convergence criterion set by \c mTolerance is met or \c mMaxIteration is reached.
     * \pre The input matrix must be square.
     * \post The protected members \c mEigenvalue and \c mEigenvector will hold the dominant pair if convergence is achieved.
     */
    virtual void solve() override;
};

#endif // POWERMETHOD_H