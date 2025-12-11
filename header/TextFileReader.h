#ifndef TESTFILEREADER_H
#define TESTFILEREADER_H

#include "Reader.h"
#include <Eigen/Dense>
#include <string>
#include <complex>

/**
 * \tparam Scalar The numeric type of the elements to be read (defaults to \c double).
 * \class TextFileReader
 * \brief Implements the abstract Reader interface to parse matrix data from a generic, space-delimited text file.
 *
 * \details The TextFileReader is designed to handle matrix input where elements are separated by
 * whitespace (spaces or tabs) and rows are delimited by newlines. It must robustly handle inconsistent
 * spacing and convert the resulting string tokens into the appropriate numeric type (\c Scalar).
 * This reader is often simpler to use than \c CSVReader for dense, regular matrices.
 *
 *
 * \ingroup IO
 * \sa Reader
 * \sa CSVReader
 */
template<typename Scalar = double>
class TextFileReader : public Reader<Scalar> {
public:
    /**
     * \brief Type alias for the specific matrix type this reader produces.
     */
    using Matrix = Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>;

    // Constructors and Destructors
    /**
     * \brief Constructs a TextFileReader object, associating it with the specified file path.
     * \param filename The path to the plain text file containing the matrix data.
     */
    TextFileReader(const std::string & filename);

    /**
     * \brief Destructor for TextFileReader.
     */
    virtual ~TextFileReader();

    // Public Method
    /**
     * \brief Reads configuration parameters from the text file or an associated configuration section.
     * \details Implementation must define how parameters (e.g., tolerance, max iterations) are embedded or referenced within the text file format.
     * \return A \c Parameters object populated with configuration settings.
     */
    virtual Parameters ReadParameters() override;

    /**
     * \brief Reads and parses the matrix data from the text file.
     * \details This is the core reading method. It opens the file, reads line by line, uses string streams
     * to tokenize the data based on whitespace, and converts each token to the \c Scalar type to build the matrix.
     * \return The matrix read from the text file as an \c Eigen::Matrix<Scalar, ...>.
     * \throw std::runtime_error If the file is inaccessible or contains non-numeric data.
     */
    virtual Matrix ReadMatrix() override;

private:
    /**
     * \brief Utility function to remove leading and trailing whitespace from a string.
     * \param str The string to be trimmed.
     * \return The trimmed string.
     */
    std::string trim(const std::string& str);
};

// --- Type aliases documentation ---

/**
 * \brief Type alias for the TextFileReader specialized for real-valued matrix input.
 * \details Used for reading matrices where elements are of type \c double.
 * \sa TextFileReader
 */
using TextFileReaderReal= TextFileReader<double>;

/**
 * \brief Type alias for the TextFileReader specialized for complex-valued matrix input.
 * \details Used for reading matrices where elements are of type \c std::complex<double>.
 * \sa TextFileReader
 */
using TextFileReaderComplex = TextFileReader<std::complex<double>>;

#endif //TESTFILEREADER_H