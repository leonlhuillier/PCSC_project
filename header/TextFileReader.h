#ifndef TESTFILEREADER_H
#define TESTFILEREADER_H

#include "Reader.h"
#include <Eigen/Dense>
#include <string>
#include <complex>


template<typename Scalar = double>
class TextFileReader : public Reader<Scalar> {
public:
    using Matrix = Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>;
    // Constructors and Destructors
    TextFileReader(const std::string & filename);
    virtual ~TextFileReader();

    // Public Method
    virtual Parameters ReadParameters() override;
    virtual Matrix ReadMatrix() override;
private:
    std::string trim(const std::string& str);
};
using TextFileReaderReal= TextFileReader<double>;
using TextFileReaderComplex = TextFileReader<std::complex<double>>;

#endif //TESTFILEREADER_H