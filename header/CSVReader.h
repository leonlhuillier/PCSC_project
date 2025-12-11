#ifndef CSVREADER_H
#define CSVREADER_H

#include "Reader.h"
#include <Eigen/Dense>
#include <string>
#include <complex>

/**
* \class CSVReader
* \brief Implements the abstract Reader interface to parse matrix data from a CSV file.
*
* \details The CSVReader is a concrete implementation of the Reader base class. It is responsible for
* opening the specified file, parsing the matrix elements based on commas and newlines, and converting
* this structured text data into an \c Eigen::MatrixXd object for use by the solvers.
* It must handle potential file errors, invalid data formats, and type conversions.
*/

template<typename Scalar = double>
class CSVReader : public Reader<Scalar> {

public:
    using Matrix = Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>;
    /**
     * \brief Constructs a CSVReader object, associating it with a specific file path.
     * \param filename The full path to the CSV file containing the matrix data. The file is assumed
     * to be a rectangular matrix where values in a row are separated by commas.
     */
    CSVReader(const std::string& filename);
    /**
    * \brief Destructor for CSVReader.
    */
    ~CSVReader() override;
// Qu'est ce que fait exactement lka fonction
    /**
     * \brief Reads and parse the matrix from the CSV file.
    * \details This is the core reading method. It opens the file, iterates through lines, tokenizes
     * based on the comma, converts string tokens to double-precision numbers, and builds
     * the \c Eigen::MatrixXd structure.
     * \return This method returns an \c Eigen::MatrixX read from the file.
     */
    Matrix ReadMatrix() override;
    /**
     * \brief Reads configuration parameters from the CSV file.
     * \details This method can be used to read settings like the expected matrix size, data precision,
     * or any solver-specific configuration stored within the input file.
     * \return A \c Parameters struct containing the read configuration settings.
     */
    Parameters ReadParameters() override;

private:
    /**
     *  \brief Private function to ignore whitespace in the CSV file.
     */
    std::string trim(const std::string& str); // to ignore whitespace
};
/**
 * \brief Type alias for a CSVReader specialized for real-valued matrices.
 * * \details Defines a concrete reader type that uses \c double as the underlying
 * numeric type for matrix elements.
 * * \sa CSVReader
 */
using CSVReaderReal = CSVReader<double>;    // LLM
/**
 * \brief Type alias for a CSVReader specialized for complex-valued matrices.
 * * \details Defines a concrete reader type that uses \c std::complex<double>
 * as the underlying numeric type for matrix elements. This reader must be used
 * when the matrix contains complex numbers.
 * * \sa CSVReader
 */
using CSVReaderComplex = CSVReader<std::complex<double>>;   // LLM



#endif // CSVREADER_H
