#include "FileWriter.h"
#include <iostream>
#include <fstream>

// Construtor
FileWriter::FileWriter(const std::string& filename) : mFilename(filename) {
    std::cout << "File " << mFilename << " created!" << std::endl;
}

// Destrcuctor
FileWriter::~FileWriter() {}

// Virtual function
void FileWriter::Write() {
    std::cout << "File " << mFilename << " written!" << std::endl;
    std::ofstream myfile;
}

