//
// Created by 32484 on 05-12-25.
//
//
// Created by fanni on 05/12/2025.
//
#include "Reader.h"
#include <iostream>
#include <string>
#include <fstream>

// Constructor
Reader::Reader(const std::string& fileName):mFilename(fileName) {
    if (!FileExists()) {
        std::cerr << "File" <<mFilename<< " does not exist!" << std::endl;
    }
}

// Destructor
Reader::~Reader() {
}

//
