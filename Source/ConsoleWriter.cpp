#include "ConsoleWriter.h"
#include <iostream>

// Constructor
ConsoleWriter::ConsoleWriter() : Writer() {}

// Destructor
ConsoleWriter::~ConsoleWriter() {}

// function
void ConsoleWriter::Write() {
    std::cout << "\n--- Results ---" << std::endl;
    std::cout << "Eigenvalue: " << mEigenvalue << std::endl;
    if (mEigenvector.size() > 0) {
        std::cout << "Eigenvector:\n" << mEigenvector << std::endl;
    } else {
        std::cout << "Eigenvector: [Not computed or empty]" << std::endl;
    }
    std::cout << "---------------\n" << std::endl;
}