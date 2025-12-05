#ifndef READER_H
#define READER_H

#include <Eigen/Dense>
#include <string>

// Assuming 'Parameters' is a struct or class you will define later for config
struct Parameters {};

class Reader {
public:
    // Constructor and Destructor
    Reader(const std::string& filename);
    virtual ~Reader();

    // Pure Virtual Methods
    virtual Parameters ReadParameters() = 0;
    virtual Eigen::MatrixXd ReadMatrix() = 0;

protected:
    // Protected Member Variable
    std::string mFilename;
};

#endif // READER_H