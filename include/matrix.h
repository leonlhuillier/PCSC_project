#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <cmath>
#include <iomanip>

class Matrix {
private:
    std::vector<std::vector<double>> data;
    size_t rows;
    size_t cols;

public:
    // Constructors
    Matrix(size_t rows, size_t cols, double init_value = 0.0);
    Matrix(const std::vector<std::vector<double>>& input_data);
    
    // Accessors
    size_t getRows() const { return rows; }
    size_t getCols() const { return cols; }
    double& operator()(size_t i, size_t j);
    const double& operator()(size_t i, size_t j) const;
    
    // Operations
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(double scalar) const;
    Matrix transpose() const;
    
    // Vector operations
    std::vector<double> operator*(const std::vector<double>& vec) const;
    
    // Utility functions
    void print() const;
    static Matrix identity(size_t n);
    static Matrix random(size_t rows, size_t cols, double min = 0.0, double max = 1.0);
    double norm() const;
    bool isSymmetric() const;
};

// Vector utility functions
double vectorNorm(const std::vector<double>& vec);
std::vector<double> normalizeVector(const std::vector<double>& vec);
double dotProduct(const std::vector<double>& a, const std::vector<double>& b);

#endif // MATRIX_H
