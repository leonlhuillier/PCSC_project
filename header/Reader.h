#ifndef READER_H
#define READER_H

#include <Eigen/Dense>
#include <string>
#include <complex>
#include "Parameters.h"


template<typename Scalar = double>
class Reader {
public:
    using Matrix = Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>;

    // File type enum
    enum class FileType {
        CSV,
        TEXT,
        UNKNOWN
    };

    // Constructor and Destructor
    Reader(const std::string& filename);
    virtual ~Reader();

    // Pure Virtual Methods
    virtual Parameters ReadParameters() = 0;
    virtual Matrix ReadMatrix() = 0;

    // File type methods
    FileType GetFileType() const;
    std::string GetFileTypeString() const;

protected:
    std::string mFilename;
    FileType mFileType;
};

// Type aliases
using ReaderReal = Reader<double>;
using ReaderComplex = Reader<std::complex<double>>;

#endif // READER_H
