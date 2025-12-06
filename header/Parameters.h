//
// Created by fanni on 05/12/2025.
//

#ifndef PCSC_PROJECT_PARAMETERS_H
#define PCSC_PROJECT_PARAMETERS_H

#include <string>
#include <iostream>

class Parameters {
public:
    // Constructor
    Parameters();

    // Setters
    void setMatrixFile(const std::string& filename);
    void setAlgorithm(const std::string& algorithm);
    void setMaxIterations(int maxIter);
    void setTolerance(double tol);
    void setShift(double shift);

    // Getters
    std::string getMatrixFile() const { return mMatrixFile; }
    std::string getAlgorithm() const { return mAlgorithm; }
    int getMaxIterations() const { return mMaxIter; }
    double getTolerance() const { return mTolerance; }
    double getShift() const { return mShift; }

    // Utility functions
    void display() const;
    bool validate() const;

private:
    std::string mMatrixFile;
    std::string mAlgorithm;
    int mMaxIter;
    double mTolerance;
    double mShift;
};

#endif // PCSC_PROJECT_PARAMETERS_H
