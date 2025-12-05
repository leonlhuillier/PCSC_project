#ifndef CONSOLEWRITER_H
#define CONSOLEWRITER_H

#include <string>

#include "Writer.h"

class ConsoleWriter : public Writer {
public:
    // Constructors and Destructors
    ConsoleWriter();
    virtual ~ConsoleWriter();

    // Public virtual Method
    virtual void Write() override;

};

#endif //CONSOLEWRITER_H