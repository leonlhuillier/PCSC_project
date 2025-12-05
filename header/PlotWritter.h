#ifndef PLOTWRITER_H
#define PLOTWRITER_H

#include <string>

#include "Writer.h"

class PlotWriter : public Writer {
public:
    // Constructors and Destructors
    PlotWriter(const std::string & filename);
    virtual ~PlotWriter();

    // Public virtual Method
    virtual void Write() override;

private:
    std::string mFilename;
};

#endif //PLOTWRITER_H