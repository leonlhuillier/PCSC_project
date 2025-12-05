#include <iostream>
#include <iomanip>
#include "matrix.h"
#include "power_method.h"
#include "qr_algorithm.h"
#include "jacobi_method.h"

void printSeparator() {
    std::cout << "\n" << std::string(70, '=') << "\n" << std::endl;
}

void demonstratePowerMethod() {
    std::cout << "POWER METHOD - Finding Dominant Eigenvalue\n";
    std::cout << std::string(70, '-') << std::endl;
    
    // Create a test matrix
    Matrix A({
        {4.0, 1.0, 2.0},
        {1.0, 3.0, 1.0},
        {2.0, 1.0, 5.0}
    });
    
    std::cout << "Input Matrix A:" << std::endl;
    A.print();
    std::cout << std::endl;
    
    auto [eigenvalue, eigenvector] = PowerMethod::compute(A);
    
    std::cout << "\nDominant Eigenvalue: " << std::fixed << std::setprecision(6) 
              << eigenvalue << std::endl;
    std::cout << "Corresponding Eigenvector: [";
    for (size_t i = 0; i < eigenvector.size(); ++i) {
        std::cout << std::setprecision(6) << eigenvector[i];
        if (i < eigenvector.size() - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

void demonstrateQRAlgorithm() {
    std::cout << "QR ALGORITHM - Finding All Eigenvalues\n";
    std::cout << std::string(70, '-') << std::endl;
    
    // Create a test matrix
    Matrix A({
        {4.0, 1.0, 2.0},
        {1.0, 3.0, 1.0},
        {2.0, 1.0, 5.0}
    });
    
    std::cout << "Input Matrix A:" << std::endl;
    A.print();
    std::cout << std::endl;
    
    std::vector<double> eigenvalues = QRAlgorithm::compute(A);
    
    std::cout << "\nAll Eigenvalues:" << std::endl;
    for (size_t i = 0; i < eigenvalues.size(); ++i) {
        std::cout << "  λ" << i+1 << " = " << std::fixed << std::setprecision(6) 
                  << eigenvalues[i] << std::endl;
    }
}

void demonstrateJacobiMethod() {
    std::cout << "JACOBI METHOD - Finding Eigenvalues of Symmetric Matrix\n";
    std::cout << std::string(70, '-') << std::endl;
    
    // Create a symmetric test matrix
    Matrix A({
        {4.0, 1.0, 2.0},
        {1.0, 3.0, 1.0},
        {2.0, 1.0, 5.0}
    });
    
    std::cout << "Input Matrix A (symmetric):" << std::endl;
    A.print();
    std::cout << std::endl;
    
    std::vector<double> eigenvalues = JacobiMethod::compute(A);
    
    std::cout << "\nAll Eigenvalues:" << std::endl;
    for (size_t i = 0; i < eigenvalues.size(); ++i) {
        std::cout << "  λ" << i+1 << " = " << std::fixed << std::setprecision(6) 
                  << eigenvalues[i] << std::endl;
    }
}

void demonstrateComparison() {
    std::cout << "COMPARISON OF ALL THREE METHODS\n";
    std::cout << std::string(70, '-') << std::endl;
    
    // Create a symmetric test matrix
    Matrix A({
        {2.0, -1.0, 0.0},
        {-1.0, 2.0, -1.0},
        {0.0, -1.0, 2.0}
    });
    
    std::cout << "Input Matrix A:" << std::endl;
    A.print();
    std::cout << std::endl;
    
    std::cout << "\n1. Power Method (dominant eigenvalue only):" << std::endl;
    auto [eigenvalue_power, eigenvector] = PowerMethod::compute(A, 1000, 1e-6);
    std::cout << "   Dominant Eigenvalue: " << std::fixed << std::setprecision(6) 
              << eigenvalue_power << std::endl;
    
    std::cout << "\n2. QR Algorithm (all eigenvalues):" << std::endl;
    std::vector<double> eigenvalues_qr = QRAlgorithm::compute(A, 1000, 1e-6);
    for (size_t i = 0; i < eigenvalues_qr.size(); ++i) {
        std::cout << "   λ" << i+1 << " = " << eigenvalues_qr[i] << std::endl;
    }
    
    std::cout << "\n3. Jacobi Method (all eigenvalues, for symmetric matrices):" << std::endl;
    std::vector<double> eigenvalues_jacobi = JacobiMethod::compute(A, 1000, 1e-9);
    for (size_t i = 0; i < eigenvalues_jacobi.size(); ++i) {
        std::cout << "   λ" << i+1 << " = " << eigenvalues_jacobi[i] << std::endl;
    }
}

int main() {
    std::cout << "\n";
    std::cout << "╔════════════════════════════════════════════════════════════════════╗\n";
    std::cout << "║        EIGENVALUE COMPUTATION - DIFFERENT METHODS DEMO            ║\n";
    std::cout << "╚════════════════════════════════════════════════════════════════════╝\n";
    
    try {
        printSeparator();
        demonstratePowerMethod();
        
        printSeparator();
        demonstrateQRAlgorithm();
        
        printSeparator();
        demonstrateJacobiMethod();
        
        printSeparator();
        demonstrateComparison();
        
        printSeparator();
        
        std::cout << "\nAll demonstrations completed successfully!" << std::endl;
        std::cout << "\nSummary of Methods:\n";
        std::cout << "1. Power Method: Fast, finds dominant eigenvalue only\n";
        std::cout << "2. QR Algorithm: Finds all eigenvalues, works for any square matrix\n";
        std::cout << "3. Jacobi Method: Finds all eigenvalues, best for symmetric matrices\n";
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
