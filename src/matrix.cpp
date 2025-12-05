#include "matrix.h"
#include <stdexcept>
#include <random>

// Constructors
Matrix::Matrix(size_t rows, size_t cols, double init_value)
    : rows(rows), cols(cols), data(rows, std::vector<double>(cols, init_value)) {}

Matrix::Matrix(const std::vector<std::vector<double>>& input_data)
    : data(input_data), rows(input_data.size()), cols(input_data[0].size()) {
    for (const auto& row : data) {
        if (row.size() != cols) {
            throw std::invalid_argument("All rows must have the same number of columns");
        }
    }
}

// Accessors
double& Matrix::operator()(size_t i, size_t j) {
    if (i >= rows || j >= cols) {
        throw std::out_of_range("Matrix index out of bounds");
    }
    return data[i][j];
}

const double& Matrix::operator()(size_t i, size_t j) const {
    if (i >= rows || j >= cols) {
        throw std::out_of_range("Matrix index out of bounds");
    }
    return data[i][j];
}

// Operations
Matrix Matrix::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }
    Matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result(i, j) = data[i][j] + other(i, j);
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Matrix dimensions must match for subtraction");
    }
    Matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result(i, j) = data[i][j] - other(i, j);
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols != other.rows) {
        throw std::invalid_argument("Matrix dimensions incompatible for multiplication");
    }
    Matrix result(rows, other.cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < other.cols; ++j) {
            double sum = 0.0;
            for (size_t k = 0; k < cols; ++k) {
                sum += data[i][k] * other(k, j);
            }
            result(i, j) = sum;
        }
    }
    return result;
}

Matrix Matrix::operator*(double scalar) const {
    Matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result(i, j) = data[i][j] * scalar;
        }
    }
    return result;
}

Matrix Matrix::transpose() const {
    Matrix result(cols, rows);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result(j, i) = data[i][j];
        }
    }
    return result;
}

// Vector operations
std::vector<double> Matrix::operator*(const std::vector<double>& vec) const {
    if (cols != vec.size()) {
        throw std::invalid_argument("Vector size must match matrix columns");
    }
    std::vector<double> result(rows, 0.0);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result[i] += data[i][j] * vec[j];
        }
    }
    return result;
}

// Utility functions
void Matrix::print() const {
    std::cout << std::fixed << std::setprecision(4);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            std::cout << std::setw(10) << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix Matrix::identity(size_t n) {
    Matrix result(n, n);
    for (size_t i = 0; i < n; ++i) {
        result(i, i) = 1.0;
    }
    return result;
}

Matrix Matrix::random(size_t rows, size_t cols, double min, double max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    
    Matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            result(i, j) = dis(gen);
        }
    }
    return result;
}

double Matrix::norm() const {
    double sum = 0.0;
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            sum += data[i][j] * data[i][j];
        }
    }
    return std::sqrt(sum);
}

bool Matrix::isSymmetric() const {
    if (rows != cols) return false;
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = i + 1; j < cols; ++j) {
            if (std::abs(data[i][j] - data[j][i]) > 1e-9) {
                return false;
            }
        }
    }
    return true;
}

// Vector utility functions
double vectorNorm(const std::vector<double>& vec) {
    double sum = 0.0;
    for (double val : vec) {
        sum += val * val;
    }
    return std::sqrt(sum);
}

std::vector<double> normalizeVector(const std::vector<double>& vec) {
    double norm = vectorNorm(vec);
    if (norm < 1e-10) {
        throw std::runtime_error("Cannot normalize zero vector");
    }
    std::vector<double> result(vec.size());
    for (size_t i = 0; i < vec.size(); ++i) {
        result[i] = vec[i] / norm;
    }
    return result;
}

double dotProduct(const std::vector<double>& a, const std::vector<double>& b) {
    if (a.size() != b.size()) {
        throw std::invalid_argument("Vectors must have the same size");
    }
    double sum = 0.0;
    for (size_t i = 0; i < a.size(); ++i) {
        sum += a[i] * b[i];
    }
    return sum;
}
