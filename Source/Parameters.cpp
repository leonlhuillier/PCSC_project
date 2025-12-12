//
// Created by fanni on 05/12/2025.
//
#include "Parameters.h"
#include <stdexcept>

Parameters::Parameters()
    : mMatrixFile(""),
      mAlgorithm("PowerMethod"),
      mMaxIter(1000),
      mTolerance(1e-6),
      mShift(0.0) {}


void Parameters::setMatrixFile(const std::string& filename) {
    if (filename.empty()) {
         throw std::invalid_argument("Matrix file is empty");
    }
    mMatrixFile = filename;
}
//detect the algorithm
void Parameters::setAlgorithm(const std::string& algorithm) {
    if (algorithm == "PowerMethod" ||
        algorithm == "ShiftedInversePowerMethod" ||
        algorithm == "QRMethod") {

        mAlgorithm = algorithm;
        } else {
            throw std::invalid_argument("Unknown algorithm type: " + algorithm);
        }
}

void Parameters::setMaxIterations(int maxIter) {
    mMaxIter = maxIter;
}

void Parameters::setShift(double shift) {
    mShift = shift;
}
void Parameters::setTolerance(double tol) {
    mTolerance= tol;
}

bool Parameters::validate() const {
    if (mTolerance <= 0) {
        std::cerr << "Tolerance must be positive" << std::endl;
        return false;
    }

    if (mMaxIter <= 0) {
        std::cerr << "MaxIterations must be positive" << std::endl;
        return false;
    }

    return true;
}

void Parameters::display() const {
    std::cout << "Matrix File:     " << mMatrixFile << "\n";
    std::cout << "Algorithm:       " << mAlgorithm << "\n";
    std::cout << "Max Iterations:  " << mMaxIter << "\n";
    std::cout << "Tolerance:       " << mTolerance << "\n";
    std::cout << "Shift:           " << mShift << "\n";
}
