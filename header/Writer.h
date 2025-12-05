#ifndef WRITER_H
#define WRITER_H

#include <Eigen/Dense>

class Writer {
public:
    // Constructor and Destructor
    Writer();
    virtual ~Writer();

    // Pure Virtual Method
    virtual void Write() = 0;
};

#endif // WRITER_H