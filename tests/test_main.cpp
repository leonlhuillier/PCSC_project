#include <iostream>
#include <cmath>
#include "matrix.h"
#include "power_method.h"
#include "qr_algorithm.h"
#include "jacobi_method.h"

bool approxEqual(double a, double b, double tolerance = 1e-4) {
    return std::abs(a - b) < tolerance;
}

int main() {
    int tests_passed = 0;
    int tests_failed = 0;
    
    std::cout << "Running Eigenvalue Computation Tests...\n" << std::endl;
    
    // Test 1: Matrix construction and operations
    std::cout << "Test 1: Matrix construction and basic operations... ";
    try {
        Matrix A(3, 3, 1.0);
        Matrix I = Matrix::identity(3);
        
        if (I(0, 0) == 1.0 && I(0, 1) == 0.0 && I(1, 1) == 1.0) {
            std::cout << "PASSED" << std::endl;
            tests_passed++;
        } else {
            std::cout << "FAILED" << std::endl;
            tests_failed++;
        }
    } catch (const std::exception& e) {
        std::cout << "FAILED: " << e.what() << std::endl;
        tests_failed++;
    }
    
    // Test 2: Power Method on a simple matrix
    std::cout << "Test 2: Power Method convergence... ";
    try {
        Matrix A({
            {2.0, 0.0},
            {0.0, 1.0}
        });
        
        auto [eigenvalue, eigenvector] = PowerMethod::compute(A, 1000, 1e-6);
        
        // Expected dominant eigenvalue is 2.0
        if (approxEqual(eigenvalue, 2.0, 1e-3)) {
            std::cout << "PASSED (eigenvalue = " << eigenvalue << ")" << std::endl;
            tests_passed++;
        } else {
            std::cout << "FAILED (expected ~2.0, got " << eigenvalue << ")" << std::endl;
            tests_failed++;
        }
    } catch (const std::exception& e) {
        std::cout << "FAILED: " << e.what() << std::endl;
        tests_failed++;
    }
    
    // Test 3: QR Algorithm
    std::cout << "Test 3: QR Algorithm... ";
    try {
        Matrix A({
            {3.0, 0.0},
            {0.0, 2.0}
        });
        
        std::vector<double> eigenvalues = QRAlgorithm::compute(A, 1000, 1e-6);
        
        // For a diagonal matrix, eigenvalues are the diagonal elements
        bool test_passed = (eigenvalues.size() == 2);
        if (test_passed) {
            // Check if we have eigenvalues close to 2 and 3 (in any order)
            bool has_2 = approxEqual(eigenvalues[0], 2.0, 0.1) || approxEqual(eigenvalues[1], 2.0, 0.1);
            bool has_3 = approxEqual(eigenvalues[0], 3.0, 0.1) || approxEqual(eigenvalues[1], 3.0, 0.1);
            test_passed = has_2 && has_3;
        }
        
        if (test_passed) {
            std::cout << "PASSED" << std::endl;
            tests_passed++;
        } else {
            std::cout << "FAILED" << std::endl;
            tests_failed++;
        }
    } catch (const std::exception& e) {
        std::cout << "FAILED: " << e.what() << std::endl;
        tests_failed++;
    }
    
    // Test 4: Jacobi Method on symmetric matrix
    std::cout << "Test 4: Jacobi Method on symmetric matrix... ";
    try {
        Matrix A({
            {2.0, 1.0},
            {1.0, 2.0}
        });
        
        std::vector<double> eigenvalues = JacobiMethod::compute(A, 1000, 1e-9);
        
        // Expected eigenvalues are 1 and 3
        bool test_passed = (eigenvalues.size() == 2);
        if (test_passed) {
            bool has_1 = approxEqual(eigenvalues[0], 1.0, 0.1) || approxEqual(eigenvalues[1], 1.0, 0.1);
            bool has_3 = approxEqual(eigenvalues[0], 3.0, 0.1) || approxEqual(eigenvalues[1], 3.0, 0.1);
            test_passed = has_1 && has_3;
        }
        
        if (test_passed) {
            std::cout << "PASSED" << std::endl;
            tests_passed++;
        } else {
            std::cout << "FAILED" << std::endl;
            tests_failed++;
        }
    } catch (const std::exception& e) {
        std::cout << "FAILED: " << e.what() << std::endl;
        tests_failed++;
    }
    
    // Test 5: Matrix symmetry check
    std::cout << "Test 5: Matrix symmetry check... ";
    try {
        Matrix symmetric({
            {1.0, 2.0},
            {2.0, 1.0}
        });
        
        Matrix nonsymmetric({
            {1.0, 2.0},
            {3.0, 1.0}
        });
        
        if (symmetric.isSymmetric() && !nonsymmetric.isSymmetric()) {
            std::cout << "PASSED" << std::endl;
            tests_passed++;
        } else {
            std::cout << "FAILED" << std::endl;
            tests_failed++;
        }
    } catch (const std::exception& e) {
        std::cout << "FAILED: " << e.what() << std::endl;
        tests_failed++;
    }
    
    // Summary
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "Test Results:" << std::endl;
    std::cout << "  Passed: " << tests_passed << std::endl;
    std::cout << "  Failed: " << tests_failed << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    
    return (tests_failed == 0) ? 0 : 1;
}
