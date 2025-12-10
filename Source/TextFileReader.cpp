//
// TextFileReader.cpp
//
#include "TextFileReader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>

// Constructor
template<typename Scalar>
TextFileReader<Scalar>::TextFileReader(const std::string &filename)
    : Reader<Scalar>(filename) {
    if (this->GetFileType() != Reader<Scalar>::FileType::TEXT) {
        std::cerr << "Warning: This file is not a TEXT file" << std::endl;
    }
    std::cout << "TEXT file: " << filename << std::endl;
}

// Destructor
template<typename Scalar>
TextFileReader<Scalar>::~TextFileReader() {}

// Trim whitespace
template<typename Scalar>
std::string TextFileReader<Scalar>::trim(const std::string& str1) {
    if (str1.empty())
        return str1;

    // Find first non-space
    int start1 = 0;
    while (start1 < str1.length() && std::isspace(str1[start1])) {
        start1++;
    }

    // Find last non-space
    int end1 = str1.length() - 1;
    while (end1 >= start1 && std::isspace(str1[end1])) {
        end1--;
    }

    return str1.substr(start1, end1 - start1 + 1);
}

// Read Matrix - Works with spaces or commas
template<typename Scalar>
typename TextFileReader<Scalar>::Matrix TextFileReader<Scalar>::ReadMatrix() {
    std::ifstream file(this->mFilename);
    if (!file.is_open()) {
        throw std::runtime_error("Opening Text file failed");
    }


    std::vector<std::vector<Scalar>> matrixData;
    std::string line;

    while (std::getline(file, line)) {
        line = trim(line);

        // Skip empty lines
        if (line.empty()) continue;

        // Stop at parameters section
        if (line.find("Algorithm") != std::string::npos) {
            break;
        }

        // Parse row - handle both spaces and commas
        std::vector<Scalar> row;
        std::stringstream ss(line);
        std::string value;

        // Try comma-separated first
        if (line.find(',') != std::string::npos) {
            // Comma-separated values
            while (std::getline(ss, value, ',')) {
                value = trim(value);
                if (!value.empty()) {
                    row.push_back(static_cast<Scalar>(std::stod(value)));
                }
            }
        } else {
            // Space-separated values
            double num;
            while (ss >> num) {
                row.push_back(static_cast<Scalar>(num));
            }
        }

        if (!row.empty()) {
            matrixData.push_back(row);
        }
    }

    file.close();

    // Validate matrix data
    if (matrixData.empty()) {
        throw std::runtime_error("No matrix found in Text file");
    }

    // Check all rows have same size
    int cols = matrixData[0].size();
    for (int i = 0; i < matrixData.size(); ++i) {
        if (matrixData[i].size() != cols) {
            throw std::runtime_error("Inconsistent row sizes in matrix");
        }
    }

    // Convert to Eigen matrix
    int rows = matrixData.size();
    Matrix matrix(rows, cols);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix(i, j) = matrixData[i][j];
        }
    }

    return matrix;
}

// Read Parameters  with COLON or COMMA separators
template<typename Scalar>
Parameters TextFileReader<Scalar>::ReadParameters() {
    std::ifstream file(this->mFilename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file");
    }

    Parameters params;
    std::string line;

    // Skip to "Algorithm" line
    while (std::getline(file, line)) {
        line = trim(line);
        if (line.find("Algorithm") != std::string::npos) {
            // Extract algorithm value
            std::string name, value;

            // Try colon separator first
            if (line.find(':') != std::string::npos) {
                int colonPos = line.find(':');
                value = trim(line.substr(colonPos + 1));
            }
            // Try comma separator
            else if (line.find(',') != std::string::npos) {
                int commaPos = line.find(',');
                value = trim(line.substr(commaPos + 1));
            }
            // Try space separator
            else {
                std::stringstream ss(line);
                ss >> name >> value;
            }

            params.setAlgorithm(value);
            break;
        }
    }

    // Read remaining parameters
    while (std::getline(file, line)) {
        line = trim(line);
        if (line.empty()) continue;

        std::string name, value;

        // Try colon separator first
        if (line.find(':') != std::string::npos) {
            int colonPos = line.find(':');
            name = trim(line.substr(0, colonPos));
            value = trim(line.substr(colonPos + 1));
        }
        // Try comma separator
        else if (line.find(',') != std::string::npos) {
            int commaPos = line.find(',');
            name = trim(line.substr(0, commaPos));
            value = trim(line.substr(commaPos + 1));
        }
        // Try space separator
        else {
            std::stringstream ss(line);
            ss >> name >> value;
        }

        // Set parameters
        if (name == "MaxIterations") {
            params.setMaxIterations(std::stoi(value));
        }
        else if (name == "Tolerance") {
            params.setTolerance(std::stod(value));
        }
        else if (name == "Shift") {
            params.setShift(std::stod(value));
        }
    }

    file.close();
    return params;
}


template class TextFileReader<double>;
template class TextFileReader<std::complex<double>>;
