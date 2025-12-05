#ifndef TESTFILEREADER_H
#define TESTFILEREADER_H

#include "Reader.h"


class TestFileReader : public Reader {
public:
    // Constructors and Destructors
    TestFileReader(const std::string & filename);
    virtual ~TestFileReader();

    // Public Method
    virtual Parameters ReadParameters() override;
    virtual Eigen::MatrixXd ReadMatrix() override;
};


#endif //TESTFILEREADER_H