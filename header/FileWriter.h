#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <string>

#include "Writer.h"

class FileWriter : public Writer {
public:
    // Constructors and Destructors
    FileWriter(const std::string & filename);
    virtual ~FileWriter();

    // Public virtual Method
    virtual void Write() override;

private:
    std::string mFilename;
};

#endif //FILEWRITER_H