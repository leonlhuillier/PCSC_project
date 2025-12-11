//
// Created by fanni on 10/12/2025.
//

#include "CSVReader.h"
#include "QRMethod.h"
#include <iostream>
#include <iomanip>
#include <complex>

#include "TextFileReader.h"

int main() {
    try {

        TextFileReader<std::complex<double>> reader("../data/test_matrix_qr.txt");

        auto matrix = reader.ReadMatrix();
        Parameters params = reader.ReadParameters();

        std::cout << " Matrix size:  " << matrix.rows() << "x" << matrix.cols() << "):" << std::endl;
        std::cout << matrix << std::endl;
        std::cout << std::endl;

        std::cout << "Parameters:" << std::endl;
        std::cout << " Max iterations : " << params.getMaxIterations() << std::endl;
        std::cout << " Tolerance      : " << std::scientific << params.getTolerance() << std::endl;
        std::cout << std::endl;

        QRMethod<std::complex<double>> qr(matrix, params);
        qr.solve();


        std::cout << "Results:" << std::endl;


        if (qr.hasConverged()) {
            std::cout << "  Converged after " << qr.getIterationCount()
                      << " iterations" << std::endl;
        } else {
            std::cout << "    Did not converge after " << qr.getIterationCount()
                      << " iterations" << std::endl;
        }
        std::cout << std::endl;

        auto allEigenvalues = qr.getAllEigenvalues();
        std::cout << "All Eigenvalues:" << std::endl;

        for (int i = 0; i < allEigenvalues.size(); ++i) {
            auto lambda = allEigenvalues(i);
            double magnitude = std::abs(lambda);

            std::cout << "   lambda" << (i+1) << " = " << std::fixed << std::setprecision(6)
                      << lambda.real() << (lambda.imag() >= 0 ? " + " : " - ")
                      << std::abs(lambda.imag()) << "i";
            std::cout << "  (|lambda| = " << magnitude << ")" << std::endl;
        }
        std::cout << std::endl;
        auto lambda_dominant = qr.getEigenvalue();
        auto v_dominant = qr.getEigenvector();

        std::cout << " Dominant Eigenvalue:" << std::endl;
        std::cout << "   lambda_max = " << lambda_dominant << std::endl;
        std::cout << "   |lambda_max| = " << std::abs(lambda_dominant) << std::endl;
        std::cout << std::endl;

        std::cout << "   Associated Eigenvector:" << std::endl;
        std::cout << "   " << v_dominant.transpose() << std::endl;
        std::cout << std::endl;


        std::cout << " (A*v = lambda*v):" << std::endl;

        auto Av = matrix * v_dominant;
        auto lambda_v = lambda_dominant * v_dominant;
        double error = (Av - lambda_v).norm();

        std::cout << "   A*v     = " << Av.transpose() << std::endl;
        std::cout << "   lambda*v     = " << lambda_v.transpose() << std::endl;
        std::cout << "   ||A*v - lambda*v|| = " << std::scientific << error << std::endl;
        std::cout << std::endl;


        std::cout << "Validation for all eigenpairs:" << std::endl;

        auto allEigenvectors = qr.getAllEigenvectors();
        bool all_valid = true;
        double max_error = 0.0;

        for (int i = 0; i < allEigenvalues.size(); ++i) {
            auto lambda_i = allEigenvalues(i);
            auto v_i = allEigenvectors.col(i);

            auto Av_i = matrix * v_i;
            auto lambda_v_i = lambda_i * v_i;
            double error_i = (Av_i - lambda_v_i).norm();

            max_error = std::max(max_error, error_i);

            std::string status = (error_i < 1e-5) ? "Test succeed with this error value:" : "Test failed with this error value:";
            std::cout << "   " << status << " lambda" << (i+1) << ": error = "
                      << std::scientific << error_i << std::endl;

            if (error_i >= 1e-5) {
                all_valid = false;
            }

        }
        std::cout << std::endl;

        std::cout << "FINAL RESULT" << std::endl;


        if (qr.hasConverged() && all_valid && max_error < 1e-5) {
            std::cout << " TEST PASSED " << std::endl;
            std::cout << "   Algorithm converged" << std::endl;
            std::cout << "   All eigenpairs are validated" << std::endl;
            std::cout << "   Maximum error: " << std::scientific << max_error << std::endl;
            return 0;
        } else {
            if (!qr.hasConverged()) {
                std::cout << "    Algorithm did not converge" << std::endl;
            }
            if (!all_valid) {
                std::cout << "   Some eigenpairs are invalid" << std::endl;
            }
            std::cout << "   Maximum error: " << std::scientific << max_error << std::endl;
            return 1;
        }

    } catch (const std::exception& e) {
        std::cerr << "\n ERROR: " << e.what() << std::endl;
        return 1;
    }
}
