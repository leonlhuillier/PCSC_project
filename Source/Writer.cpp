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


// TextFileWriter class


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
