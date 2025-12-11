#ifndef EIGENVALUE_H
#define EIGENVALUE_H

#include <Eigen/Dense>
#include <complex>
#include "Parameters.h"
/**
 * \class Eigenvalue
 * \brief Abstract base class for all numerical methods used to solve eigenvalue problems.
 *
 * \details The Eigenvalue class provides a uniform interface for all solver strategies.
 * It manages the common input data (the matrix A) and configuration parameters,
 * as well as the storage for the final results.
 * This class uses the Template Method Pattern, where the concrete \c solve()
 * method is implemented by derived classes.
 */
template<typename Scalar>
class Eigenvalue {
public:
    using Matrix = Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>;
    using Vector = Eigen::Matrix<Scalar, Eigen::Dynamic, 1>;
    using RealScalar = typename Eigen::NumTraits<Scalar>::Real;

    /**
     * \brief Default constructor for Eigenvalue.
     * \param matrix It contains the input matrix.
     * \param params It contains all the configuration settings,
     * such as tolerance and maximum number of iterations.
     */
    Eigenvalue(const Matrix& matrix, const Parameters& params);
    /**
    * \brief Default destructor for Eigenvalue.
    */
    virtual ~Eigenvalue();

    // Public Methods
    /**
     * \brief Pure virtual method which compute eigenvalue and the associated eigenvector.
     * \pre The matrix \c mMatrix must be loaded, initialized and square.
     */
    virtual void solve() = 0;
    /**
     * \brief Sets the convergence tolerance ($\epsilon$).
     * \param tolerance The maximum acceptable error or change between successive iterations.
     */
    void setTolerance(double tolerance);

    /**
     * \brief Sets the matrix.
     * \param matrix The matrix obtained from the reader file.
     */
    void setMatrix(const Matrix& matrix);
    /**
     * \brief Sets the maximum number of iterations.
     * \param maxIteration The upper limit on the number of steps the iterative solver will run.
     */
    void setMaxIteration(int maxIteration);
    /**
     * \brief Checks if the last call to \c solve() resulted in convergence.
     * \return \c true if the algorithm converged within the given tolerance and max iterations, \c false otherwise.
     */
    bool hasConverged() const;
    /**
     * \brief Retrieves the computed eigenvalue.
     * \pre The \c solve() method must have been executed.
     * \return The calculated eigenvalue ($\lambda$).
     */
    Scalar getEigenvalue() const;
    /**
     * \brief Retrieves the computed eigenvector.
     * \pre The \c solve() method must have been executed.
     * \return The calculated eigenvector ($x$).
     */
    Vector getEigenvector() const;
    /**
     * \brief Retrieves the current convergence tolerance.
     * \return The set tolerance value.
     */
    double getTolerance() const;
    /**
     * \brief Retrieves the current maximum iteration limit.
     * \return The set maximum iteration value.
     */
    int getMaxIterations() const;
    /**
     * \brief Retrieves the number of iterations
     */
    int getIterationCount() const;

    /**
     * \brief Check whether the matrix is invertible.
     */
    bool IsInvertible() const;


protected:
    /**
     * \brief The square matrix for which the eigenvalue problem is being solved.
     */
    Matrix mMatrix;
    /**
     * \brief The computed eigenvector corresponding to \c mEigenvalue.
     */
    Vector mEigenvector;
    /**
     * \brief The computed eigenvalue.
     */
    Scalar mEigenvalue;
    /**
     * \brief The shift used for \sa ShiftedInversePowerMethod
     */
    Scalar mShift;
    /**
     * \brief Configuration parameters for the solver.
     */
    Parameters mParams;
    /**
     * \brief The maximum number of iterations allowed for the solver.
     */
    int mMaxIteration;
    /**
     * \brief The convergence threshold ($\epsilon$).
     */
    double mTolerance;
    /**
     * \brief Internal flag to track if the solver converged successfully.
     */
    bool mConverged;
    /**
     * \brief The count of interation to reach an admissible result.
     */
    int mIterationCount;
};
/**
 * \brief Type alias for the base solver class operating on real numbers.
 * * \details Defines the base class for solvers that handle matrices with real-valued elements
 * (\c double). Concrete solvers like \c PowerMethodReal and \c QRMethodReal would inherit
 * from this specialization.
 * * \sa Eigenvalue
 */
using EigenvalueReal = Eigenvalue<double>;
/**
 * \brief Type alias for the base solver class operating on complex numbers.
 * * \details Defines the base class for solvers that handle matrices with complex-valued elements
 * (\c std::complex<double>). This specialization ensures that all internal calculations,
 * including dot products and norms, use complex arithmetic required for solving complex
 * eigenvalue problems (e.g., those arising in non-Hermitian systems).
 * * \sa Eigenvalue
 */
using EigenvalueComplex = Eigenvalue<std::complex<double>>;

#endif // EIGENVALUE_H
