#ifndef CSVREADER_H
#define CSVREADER_H

#include "Reader.h"


class CSVReader : public Reader {
public:
    // Constructors and Destructors
    CSVReaderReader(const std::string & filename);
    virtual ~CSVReader();

    // Public Method
    virtual Parameters ReadParameters() override;
    virtual Eigen::MatrixXd ReadMatrix() override;
};


#endif //CSVREADER_H