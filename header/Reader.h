#ifndef READER_H
#define READER_H

#include <Eigen/Dense>
#include <string>
#include <complex>
#include "Parameters.h"


/**
 * \tparam Scalar The numeric type of the elements to be read into the matrix (e.g., \c double, \c std::complex<double>).
 * \class Reader
 * \brief Abstract base class providing a uniform interface for reading matrix data and configuration parameters from various input sources.
 *
 * \details The Reader class uses the strategy pattern for handling file input. Derived concrete classes,
 * like \c CSVReader, \c TextFileReader, must implement the pure virtual methods to define the specific parsing logic
 * for their respective file formats. This templated structure ensures that the same I/O architecture can handle both
 * real and complex data types.
 */
template<typename Scalar>
class Reader {
public:
    /**
     * \brief Type alias for the matrix type that this reader will output, based on the template parameter \c Scalar.
     */
    using Matrix = Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>;

    /**
     * \enum FileType
     * \brief Enumeration of supported input file formats.
     */
    enum class FileType {
        /** \brief Comma-Separated Values file format. */
        CSV,
        /** \brief Plain text file format (e.g., space or tab delimited). */
        TEXT,
        /** \brief Default or unrecognized file format. */
        UNKNOWN
    };

    // Constructor and Destructor
    /**
     * \brief Constructor for the Reader base class.
     * \details Initializes the reader and stores the path to the input file. The actual file parsing
     * is deferred to the derived classes.
     * \param filename Path to the input file to be read.
     */
    Reader(const std::string& filename);

    /**
     * \brief Virtual destructor. Ensures correct cleanup of derived class objects.
     */
    virtual ~Reader();

    // Pure Virtual Methods
    /**
     * \brief Pure virtual method for reading configuration parameters.
     * \details Derived classes must implement this to extract application settings (tolerance, shift, etc.)
     * from the input source, typically into a \c Parameters object.
     * \return A \c Parameters object populated with configuration settings.
     */
    virtual Parameters ReadParameters() = 0;

    /**
     * \brief Pure virtual method for reading the main matrix data.
     * \details Derived classes must implement the parsing logic to convert the file content into the
     * specified matrix type (\c Matrix).
     * \return The matrix read from the input source as an \c Eigen::Matrix<Scalar, ...>.
     */
    virtual Matrix ReadMatrix() = 0;

    // File type methods
    /**
     * \brief Gets the identified file type.
     * \return The \c FileType enumeration value.
     */
    FileType GetFileType() const;

    /**
     * \brief Returns the file type as a human-readable string.
     * \return A string representing the file type (e.g., "CSV", "TEXT").
     */
    std::string GetFileTypeString() const;

protected:
    /**
     * \brief Path to the matrix data file.
     */
    std::string mFilename;

    /**
     * \brief The determined file type of the input source.
     */
    FileType mFileType;
};


/**
 * \brief Type alias for the base Reader class specialized for real-valued matrix input.
 * \details Used for reading matrices where elements are of type \c double.
 * \sa Reader
 */
using ReaderReal = Reader<double>;

/**
 * \brief Type alias for the base Reader class specialized for complex-valued matrix input.
 * \details Used for reading matrices where elements are of type \c std::complex<double>.
 * \sa Reader
 */
using ReaderComplex = Reader<std::complex<double>>;

#endif // RE ADER_H
