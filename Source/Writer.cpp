#include "Writer.h"
#include <fstream>
#include <iostream>


Writer::Writer(const std::string& filename) : mFilename(filename) {}

CSVWriter::CSVWriter(const std::string& filename) : Writer(filename) {}

void CSVWriter::write(double eigenvalue,
                     const Eigen::VectorXd& eigenvector,
                     int iterations,
                     bool converged) const {
    std::ofstream file(mFilename);

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << mFilename << " for writing" << std::endl;
        return;
    }

    // Write header
    file << "Eigenvalue,Iterations,Converged" << std::endl;
    file << eigenvalue << "," << iterations << "," << (converged ? "Yes" : "No") << std::endl;
    file << std::endl;

    // Write eigenvector
    file << "Eigenvector Components" << std::endl;
    for (int i = 0; i < eigenvector.size(); ++i) {
        file << eigenvector(i) << std::endl;
    }

    file.close();
    std::cout << "Results written to " << mFilename << std::endl;
}

void CSVWriter::write(std::complex<double> eigenvalue,
                     const Eigen::VectorXcd& eigenvector,
                     int iterations,
                     bool converged) const {
    std::ofstream file(mFilename);

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << mFilename << " for writing" << std::endl;
        return;
    }

    // Write header
    file << "Eigenvalue_Real,Eigenvalue_Imag,Iterations,Converged" << std::endl;
    file << eigenvalue.real() << "," << eigenvalue.imag() << ","
         << iterations << "," << (converged ? "Yes" : "No") << std::endl;
    file << std::endl;

    // Write eigenvector
    file << "Eigenvector_Real,Eigenvector_Imag" << std::endl;
    for (int i = 0; i < eigenvector.size(); ++i) {
        file << eigenvector(i).real() << "," << eigenvector(i).imag() << std::endl;
    }

    file.close();
    std::cout << "Results written to " << mFilename << std::endl;
}


void CSVWriter::writeAll(const Eigen::VectorXd& eigenvalues,
                        const Eigen::MatrixXd& eigenvectors,
                        int iterations,
                        bool converged) const {
    std::ofstream file(mFilename);

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << mFilename << " for writing" << std::endl;
        return;
    }

    file << "QR METHOD - ALL EIGENVALUES AND EIGENVECTORS" << std::endl;
    file << "Iterations," << iterations << std::endl;
    file << "Converged," << (converged ? "Yes" : "No") << std::endl;
    file << std::endl;

    // Write all eigenvalues
    file << "All Eigenvalues" << std::endl;
    for (int i = 0; i < eigenvalues.size(); ++i) {
        file << "lambda_" << (i+1) << "," << eigenvalues(i) << std::endl;
    }
    file << std::endl;

    // Write all eigenvectors
    file << "All Eigenvectors (columns)" << std::endl;
    for (int i = 0; i < eigenvectors.rows(); ++i) {
        for (int j = 0; j < eigenvectors.cols(); ++j) {
            file << eigenvectors(i, j);
            if (j < eigenvectors.cols() - 1) file << ",";
        }
        file << std::endl;
    }

    file.close();
    std::cout << "All results written to " << mFilename << std::endl;
}

void CSVWriter::writeAll(const Eigen::VectorXcd& eigenvalues,
                        const Eigen::MatrixXcd& eigenvectors,
                        int iterations,
                        bool converged) const {
    std::ofstream file(mFilename);

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << mFilename << " for writing" << std::endl;
        return;
    }

    file << "QR METHOD - ALL EIGENVALUES AND EIGENVECTORS (COMPLEX)" << std::endl;
    file << "Iterations," << iterations << std::endl;
    file << "Converged," << (converged ? "Yes" : "No") << std::endl;
    file << std::endl;

    // Write all eigenvalues
    file << "Eigenvalue_Index,Real_Part,Imaginary_Part" << std::endl;
    for (int i = 0; i < eigenvalues.size(); ++i) {
        file << "lambda_" << (i+1) << ","
             << eigenvalues(i).real() << ","
             << eigenvalues(i).imag() << std::endl;
    }
    file << std::endl;

    // Write all eigenvectors
    file << "All Eigenvectors (Real parts)" << std::endl;
    for (int i = 0; i < eigenvectors.rows(); ++i) {
        for (int j = 0; j < eigenvectors.cols(); ++j) {
            file << eigenvectors(i, j).real();
            if (j < eigenvectors.cols() - 1) file << ",";
        }
        file << std::endl;
    }
    file << std::endl;

    file << "All Eigenvectors (Imaginary parts)" << std::endl;
    for (int i = 0; i < eigenvectors.rows(); ++i) {
        for (int j = 0; j < eigenvectors.cols(); ++j) {
            file << eigenvectors(i, j).imag();
            if (j < eigenvectors.cols() - 1) file << ",";
        }
        file << std::endl;
    }

    file.close();
    std::cout << "All results written to " << mFilename << std::endl;
}




TextFileWriter::TextFileWriter(const std::string& filename) : Writer(filename) {}

void TextFileWriter::write(double eigenvalue,
                          const Eigen::VectorXd& eigenvector,
                          int iterations,
                          bool converged) const {
    std::ofstream file(mFilename);

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << mFilename << " for writing" << std::endl;
        return;
    }

    // Write title

    file << "     EIGENVALUE COMPUTATION RESULTS     " << std::endl;


    // Write convergence status
    file << "Convergence Status: " << (converged ? "CONVERGED" : "NOT CONVERGED") << std::endl;
    file << "Number of Iterations: " << iterations << std::endl << std::endl;

    // Write eigenvalue
    file << "Dominant Eigenvalue: " << eigenvalue << std::endl << std::endl;

    // Write eigenvector
    file << "Corresponding Eigenvector:" << std::endl;
    for (int i = 0; i < eigenvector.size(); ++i) {
        file << "  v[" << i << "] = " << eigenvector(i) << std::endl;
    }


    file.close();
    std::cout << "Results written to " << mFilename << std::endl;
}

void TextFileWriter::write(std::complex<double> eigenvalue,
                           const Eigen::VectorXcd& eigenvector,
                           int iterations,
                           bool converged) const {
    std::ofstream file(mFilename);

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << mFilename << " for writing" << std::endl;
        return;
    }

    // Write title

    file << "     EIGENVALUE COMPUTATION RESULTS     " << std::endl;

    // Write convergence status
    file << "Convergence Status: " << (converged ? "CONVERGED" : "NOT CONVERGED") << std::endl;
    file << "Number of Iterations: " << iterations << std::endl << std::endl;

    // Write eigenvalue
    file << "Dominant Eigenvalue: " << eigenvalue.real();
    if (eigenvalue.imag() >= 0) {
        file << " + " << eigenvalue.imag() << "i" << std::endl << std::endl;
    } else {
        file << " - " << -eigenvalue.imag() << "i" << std::endl << std::endl;
    }

    // Write eigenvector
    file << "Corresponding Eigenvector:" << std::endl;
    for (int i = 0; i < eigenvector.size(); ++i) {
        file << "  v[" << i << "] = " << eigenvector(i).real();
        if (eigenvector(i).imag() >= 0) {
            file << " + " << eigenvector(i).imag() << "i" << std::endl;
        } else {
            file << " - " << -eigenvector(i).imag() << "i" << std::endl;
        }
    }

    file.close();
    std::cout << "Results written to " << mFilename << std::endl;
}
void TextFileWriter::writeAll(const Eigen::VectorXd& eigenvalues,
                              const Eigen::MatrixXd& eigenvectors,
                              int iterations,
                              bool converged) const {
    std::ofstream file(mFilename);

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << mFilename << " for writing" << std::endl;
        return;
    }

    file << "  QR METHOD - ALL EIGENVALUES/VECTORS  " << std::endl;


    file << "Convergence Status: " << (converged ? "CONVERGED" : "NOT CONVERGED") << std::endl;
    file << "Number of Iterations: " << iterations << std::endl << std::endl;

    file << "ALL EIGENVALUES:" << std::endl;
    for (int i = 0; i < eigenvalues.size(); ++i) {
        file << "  lambda_" << (i+1) << " = " << eigenvalues(i) << std::endl;
    }
    file << std::endl;

    file << "ALL EIGENVECTORS:" << std::endl;
    for (int i = 0; i < eigenvectors.cols(); ++i) {
        file << "\nEigenvector v_" << (i+1) << ":" << std::endl;
        for (int j = 0; j < eigenvectors.rows(); ++j) {
            file << "  v[" << j << "] = " << eigenvectors(j, i) << std::endl;
        }
    }

    file.close();
    std::cout << "All results written to " << mFilename << std::endl;
}


void TextFileWriter::writeAll(const Eigen::VectorXcd& eigenvalues,
                              const Eigen::MatrixXcd& eigenvectors,
                              int iterations,
                              bool converged) const {
    std::ofstream file(mFilename);

    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << mFilename << " for writing" << std::endl;
        return;
    }

    file << "  QR METHOD - ALL EIGENVALUES/VECTORS  " << std::endl;
    file << "           (COMPLEX NUMBERS)           " << std::endl;


    file << "Convergence Status: " << (converged ? "CONVERGED" : "NOT CONVERGED") << std::endl;
    file << "Number of Iterations: " << iterations << std::endl << std::endl;

    file << "ALL EIGENVALUES:" << std::endl;
    for (int i = 0; i < eigenvalues.size(); ++i) {
        file << "  lambda_" << (i+1) << " = " << eigenvalues(i).real();
        if (eigenvalues(i).imag() >= 0) {
            file << " + " << eigenvalues(i).imag() << "i" << std::endl;
        } else {
            file << " - " << -eigenvalues(i).imag() << "i" << std::endl;
        }
    }
    file << std::endl;

    file << "ALL EIGENVECTORS:" << std::endl;
    for (int i = 0; i < eigenvectors.cols(); ++i) {
        file << "\nEigenvector v_" << (i+1) << ":" << std::endl;
        for (int j = 0; j < eigenvectors.rows(); ++j) {
            file << "  v[" << j << "] = " << eigenvectors(j, i).real();
            if (eigenvectors(j, i).imag() >= 0) {
                file << " + " << eigenvectors(j, i).imag() << "i" << std::endl;
            } else {
                file << " - " << -eigenvectors(j, i).imag() << "i" << std::endl;
            }
        }
    }

    file.close();
    std::cout << "All results written to " << mFilename << std::endl;
}