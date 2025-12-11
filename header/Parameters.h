//
// Created by fanni on 05/12/2025.
//

#ifndef PCSC_PROJECT_PARAMETERS_H
#define PCSC_PROJECT_PARAMETERS_H

#include <string>
#include <iostream>

/**
 * \class Parameters
 * \brief A container class used to hold all necessary configuration settings for the Eigenvalue Solver application.
 *
 * \details This class centralizes user-defined parameters. It encapsulates settings such as
 * the input matrix file location, the specific eigenvalue algorithm to be used, and numerical
 * convergence criteria.
 */
class Parameters {
public:
    /**
     * \brief Default constructor. Initializes all parameters to default safe values (e.g., max iterations=100, tolerance=1e-6).
     */
    Parameters();

    /**
     * \brief Sets the path to the input file containing the matrix data.
     * \param filename The path to the matrix file.
     */
    void setMatrixFile(const std::string& filename);

    /**
     * \brief Sets the name of the eigenvalue algorithm to be executed.
     * \param algorithm A string identifier for the solver strategy.
     */
    void setAlgorithm(const std::string& algorithm);

    /**
     * \brief Sets the maximum number of iterations allowed for iterative solvers.
     * \param maxIter The upper integer limit on iterations before the solver gives up.
     */
    void setMaxIterations(int maxIter);

    /**
     * \brief Sets the convergence tolerance ($\epsilon$).
     * \param tol The maximum acceptable difference between successive calculated values for convergence.
     */
    void setTolerance(double tol);

    /**
     * \brief Sets the shift value for the Shifted Inverse Power Method.
     * \details This parameter determines the target eigenvalue that the method will converge to.
     * \param shift The real number used as the shift factor.
     */
    void setShift(double shift);

    /**
     * \brief Gets the path to the input matrix file.
     * \return The file path string.
     */
    std::string getMatrixFile() const { return mMatrixFile; }

    /**
     * \brief Gets the name of the configured algorithm.
     * \return The algorithm identifier string.
     */
    std::string getAlgorithm() const { return mAlgorithm; }

    /**
     * \brief Gets the maximum number of iterations.
     * \return The maximum iteration limit.
     */
    int getMaxIterations() const { return mMaxIter; }

    /**
     * \brief Gets the convergence tolerance.
     * \return The tolerance value.
     */
    double getTolerance() const { return mTolerance; }

    /**
     * \brief Gets the shift value ($\mu$) for relevant algorithms.
     * \return The shift value.
     */
    double getShift() const { return mShift; }

    /**
     * \brief Prints all current configuration settings to the standard output.
     * \details Useful for debugging and verifying that parameters were loaded correctly.
     */
    void display() const;

    /**
     * \brief Validates the current set of parameters before execution.
     * \details Checks for mandatory settings (e.g., matrix file path is not empty)
     * and logical consistency (e.g., tolerance is positive, max iterations > 0).
     * \return \c true if all parameters are valid, \c false otherwise.
     */
    bool validate() const;

private:
    /**
     * \brief File path for the input matrix data.
     */
    std::string mMatrixFile;

    /**
     * \brief The chosen eigenvalue algorithm identifier.
     */
    std::string mAlgorithm;

    /**
     * \brief Maximum number of iterations.
     */
    int mMaxIter;

    /**
     * \brief Convergence tolerance.
     */
    double mTolerance;

    /**
     * \brief Shift value.
     */
    double mShift;
};

#endif // PCSC_PROJECT_PARAMETERS_H
