#include "FileWriter.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Construtor
FileWriter::FileWriter(const std::string& filename) : mFilename(filename) {
    std::cout << "File " << mFilename << " created!" << std::endl;
}

// Destrcuctor
FileWriter::~FileWriter() {}

// Virtual function
void FileWriter::Write() {
    std::ofstream file(mFilename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for writing: " << mFilename << std::endl;
        return;
    }
    if (mEigenvector.size() > 0) {
        // Use a stringstream to format the Eigen vector nicely
        std::stringstream ss;       // Use of LLMs here, add clarity in the file when writing done the vector
        ss << mEigenvector;         // Use of LLMs here, add clarity in the file when writing done the vector
        file << ss.str() << "\n";
    } else {
        file << "[Not computed or empty]\n";
    }

    file.close();
    std::cout << "Results successfully written to: " << mFilename << std::endl;
}

