#ifndef WRITER_H
#define WRITER_H

#include <string>
#include <complex>
#include <Eigen/Dense>

/**
 * \class Writer
 * \brief Abstract base class providing a polymorphic interface for outputting solver results to various destinations.
 *
 * \details The Writer class employs the \b Strategy \b Pattern, allowing the application to easily switch
 * between output formats (e.g., CSV, plain text, console) without modifying the solver logic.
 * This base class defines a set of overloaded pure virtual \c write methods to handle the four possible result scenarios:
 * 1. Single eigenvalue/eigenvector pair (real or complex).
 * 2. Full set of eigenvalues/eigenvectors (real or complex).
 * * All derived classes must implement all four \c write signatures to correctly handle any solver result.
 *
 *
 * \ingroup IO
 */
class Writer {
protected:
    /**
     * \brief The target file path or identifier for output.
     */
    std::string mFilename;

public:
    /**
     * \brief Constructor for the Writer base class.
     * \param filename The path or identifier for the output destination (e.g., a file path).
     */
    Writer(const std::string& filename);

    /**
     * \brief Virtual destructor. Set to default as no resource cleanup is managed here.
     */
    virtual ~Writer() = default;


    // --- Single Result Write Methods (For Power Methods, etc.) ---

    /**
     * \brief Writes a single real-valued eigenvalue/eigenvector pair.
     * \details Used by solvers like the standard Power Method which typically return only the dominant pair.
     * \param eigenvalue The computed real eigenvalue $\lambda$.
     * \param eigenvector The corresponding real eigenvector $x$.
     * \param iterations The total number of iterations performed.
     * \param converged Boolean indicating whether the solver reached convergence.
     */
    virtual void write(double eigenvalue,
                      const Eigen::VectorXd& eigenvector,
                      int iterations,
                      bool converged) const = 0;

    /**
     * \brief Writes a single complex-valued eigenvalue/eigenvector pair.
     * \details Required for solvers that handle complex matrices or produce complex results.
     * \param eigenvalue The computed complex eigenvalue $\lambda$.
     * \param eigenvector The corresponding complex eigenvector $x$.
     * \param iterations The total number of iterations performed.
     * \param converged Boolean indicating whether the solver reached convergence.
     */
    virtual void write(std::complex<double> eigenvalue,
                      const Eigen::VectorXcd& eigenvector,
                      int iterations,
                      bool converged) const = 0;

    // --- All Results Write Methods (For QR Method, etc.) ---

    /**
     * \brief Writes the entire set of real-valued eigenvalues and eigenvectors.
     * \details Used by solvers like the QR Method which compute all solutions simultaneously.
     * \param eigenvalues A vector containing all computed real eigenvalues.
     * \param eigenvectors A matrix containing all computed real eigenvectors (in columns).
     * \param iterations The total number of iterations performed.
     * \param converged Boolean indicating whether the solver reached convergence.
     */
    virtual void writeAll(const Eigen::VectorXd& eigenvalues,
                         const Eigen::MatrixXd& eigenvectors,
                         int iterations,
                         bool converged) const = 0;

    /**
     * \brief Writes the entire set of complex-valued eigenvalues and eigenvectors.
     * \details Required for QR Method or similar solvers handling complex matrices.
     * \param eigenvalues A vector containing all computed complex eigenvalues.
     * \param eigenvectors A matrix containing all computed complex eigenvectors (in columns).
     * \param iterations The total number of iterations performed.
     * \param converged Boolean indicating whether the solver reached convergence.
     */
    virtual void writeAll(const Eigen::VectorXcd& eigenvalues,
                         const Eigen::MatrixXcd& eigenvectors,
                         int iterations,
                         bool converged) const = 0;
};

/**
 * \class CSVWriter
 * \brief Implements the Writer interface for outputting results to a Comma-Separated Values (CSV) file.
 *
 * \details The CSVWriter formats the solver output (eigenvalues, eigenvectors, metadata) into a structured
 * CSV format, making it easy to import the results into spreadsheet software or other data analysis tools.
 * It must define a clear and consistent schema for both single and full result sets, including headers
 * for metadata.
 * * \ingroup IO
 * \sa Writer
 */
class CSVWriter : public Writer {
public:
    /**
     * \brief Constructs a CSVWriter object.
     * \param filename The path to the output CSV file.
     */
    CSVWriter(const std::string& filename);

    /**
     * \brief Writes a single real-valued eigenvalue/eigenvector pair to the CSV file.
     * \copydoc Writer::write(double, const Eigen::VectorXd&, int, bool)
     */
    void write(double eigenvalue,
              const Eigen::VectorXd& eigenvector,
              int iterations,
              bool converged) const override;

    /**
     * \brief Writes a single complex-valued eigenvalue/eigenvector pair to the CSV file.
     * \copydoc Writer::write(std::complex<double>, const Eigen::VectorXcd&, int, bool)
     */
    void write(std::complex<double> eigenvalue,
              const Eigen::VectorXcd& eigenvector,
              int iterations,
              bool converged) const override;

    /**
     * \brief Writes the entire set of real-valued eigenvalues and eigenvectors to the CSV file.
     * \copydoc Writer::writeAll(const Eigen::VectorXd&, const Eigen::MatrixXd&, int, bool)
     */
    void writeAll(const Eigen::VectorXd& eigenvalues,
                 const Eigen::MatrixXd& eigenvectors,
                 int iterations,
                 bool converged) const override;

    /**
     * \brief Writes the entire set of complex-valued eigenvalues and eigenvectors to the CSV file.
     * \copydoc Writer::writeAll(const Eigen::VectorXcd&, const Eigen::MatrixXcd&, int, bool)
     */
    void writeAll(const Eigen::VectorXcd& eigenvalues,
                 const Eigen::MatrixXcd& eigenvectors,
                 int iterations,
                 bool converged) const override;
};

/**
 * \class TextFileWriter
 * \brief Implements the Writer interface for outputting results to a generic, human-readable text file.
 *
 * \details The TextFileWriter provides a simple, formatted output designed for easy human inspection,
 * rather than programmatic parsing. It should use clear labels, alignment, and standard formatting
 * to present the eigenvalues, eigenvectors, and solver metadata.
 * * \ingroup IO
 * \sa Writer
 */
class TextFileWriter : public Writer {
public:
    /**
     * \brief Constructs a TextFileWriter object.
     * \param filename The path to the output plain text file.
     */
    TextFileWriter(const std::string& filename);

    /**
     * \brief Writes a single real-valued eigenvalue/eigenvector pair to a text file.
     * \copydoc Writer::write(double, const Eigen::VectorXd&, int, bool)
     */
    void write(double eigenvalue,
              const Eigen::VectorXd& eigenvector,
              int iterations,
              bool converged) const override;

    /**
     * \brief Writes a single complex-valued eigenvalue/eigenvector pair to a text file.
     * \copydoc Writer::write(std::complex<double>, const Eigen::VectorXcd&, int, bool)
     */
    void write(std::complex<double> eigenvalue,
              const Eigen::VectorXcd& eigenvector,
              int iterations,
              bool converged) const override;

    /**
     * \brief Writes the entire set of real-valued eigenvalues and eigenvectors to a text file.
     * \copydoc Writer::writeAll(const Eigen::VectorXd&, const Eigen::MatrixXd&, int, bool)
     */
    void writeAll(const Eigen::VectorXd& eigenvalues,
                 const Eigen::MatrixXd& eigenvectors,
                 int iterations,
                 bool converged) const override;

    /**
     * \brief Writes the entire set of complex-valued eigenvalues and eigenvectors to a text file.
     * \copydoc Writer::writeAll(const Eigen::VectorXcd&, const Eigen::MatrixXcd&, int, bool)
     */
    void writeAll(const Eigen::VectorXcd& eigenvalues,
                 const Eigen::MatrixXcd& eigenvectors,
                 int iterations,
                 bool converged) const override;
};

#endif // WRITER_H
