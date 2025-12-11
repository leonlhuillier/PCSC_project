#ifndef SHIFTEDINVERSEPOWERMETHOD_H
#define SHIFTEDINVERSEPOWERMETHOD_H

#include "Eigenvalue.h"

/**
 * \tparam Scalar The underlying numeric type of the matrix elements (e.g., \c double, \c std::complex<double>).
 * \class ShiftedInversePowerMethod
 * \brief Implements the iterative Shifted Inverse Power Method to find the eigenvalue closest to a specified shift value $\mu$.
 *
 * \details This method combines the principles of the Inverse Power Method and eigenvalue shifting. The standard
 * Inverse Power Method finds the eigenvalue closest to zero. By applying a shift $\mu$, it solves the system
 * associated with the matrix $(A - \mu I)^{-1}$, which has eigenvalues $1/(\lambda_i - \mu)$. The largest eigenvalue
 * of this shifted inverse matrix corresponds to the eigenvalue $\lambda$ of $A$ that is closest to $\mu$.
 * This technique is invaluable when high accuracy is required for a specific, known eigenvalue location.
 *
 *
 * \ingroup Solvers
 * \sa PowerMethod
 * \sa Eigenvalue
 */
template<typename Scalar>
class ShiftedInversePowerMethod : public Eigenvalue<Scalar> {
public:
    /**
     * \brief Type alias for the matrix type used by the solver (e.g., \c Eigen::MatrixXd).
     */
    using Matrix = typename Eigenvalue<Scalar>::Matrix;

    /**
     * \brief Type alias for the vector type used by the solver.
     */
    using Vector = typename Eigenvalue<Scalar>::Vector;

    // Constructors and Destructor
    /**
     * \brief Default constructor. Initializes the solver with default parameters.
     */
    ShiftedInversePowerMethod();

    /**
     * \brief Parameterized constructor to initialize the solver with the matrix and configuration settings.
     * \details Sets the input matrix and extracts configuration parameters, particularly the shift value $\mu$,
     * from the \c Parameters object.
     * \param matrix The input matrix $A$.
     * \param params A structure containing the configuration settings, including the shift $\mu$.
     */
    ShiftedInversePowerMethod(const Matrix& matrix, const Parameters& params);

    /**
     * \brief Destructor for ShiftedInversePowerMethod.
     */
    virtual ~ShiftedInversePowerMethod();

    // Overridden Method
    /**
     * \brief Executes the Shifted Inverse Power Method algorithm.
     * \details The iterative process involves solving the linear system $(A - \mu I)x_{k+1} = x_k$
     * in each step. This typically requires computing the LU decomposition of the shifted matrix $(A - \mu I)$ once.
     * \pre The input matrix must be square, and the shift $\mu$ must not be an exact eigenvalue of $A$.
     * \post The protected members \c mEigenvalue and \c mEigenvector will hold the eigenvalue pair closest to $\mu$ if convergence is achieved.
     */
    virtual void solve() override;
};

#endif // SHIFTEDINVERSEPOWERMETHOD_H