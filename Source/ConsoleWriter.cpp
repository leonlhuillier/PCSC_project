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
    std::cout << "Eigenvector:\n" << mEigenvector << std::endl;
    std::cout << "---------------\n" << std::endl;
}