#ifndef CSVREADER_H
#define CSVREADER_H

#include "Reader.h"
#include <Eigen/Dense>
#include <string>
#include <complex>

template<typename Scalar = double>
class CSVReader : public Reader<Scalar> {

public:
    using Matrix = Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>;
    CSVReader(const std::string& filename);
    ~CSVReader() override;

    Matrix ReadMatrix() override;
    Parameters ReadParameters() override;

private:
    std::string trim(const std::string& str); // to ignore whitespace
};

using CSVReaderReal = CSVReader<double>;
using CSVReaderComplex = CSVReader<std::complex<double>>;



#endif // CSVREADER_H
