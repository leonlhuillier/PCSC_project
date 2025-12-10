//
// Created by fanni on 10/12/2025.
//

//
// Created by fanni on 10/12/2025.
//

#include "CSVReader.h"
#include "QRMethod.h"

int main() {
    try {
        CSVReader reader("../data/test_matrix_qr.csv");
        auto matrix=reader.ReadMatrix();

        std::cout <<" Matrix:\n"<< matrix<<"\n" << std::endl;
        Parameters params=reader.ReadParameters();


        std::cout << "Max iterations: " << params.getMaxIterations() << std::endl;
        std::cout << "Tolerance: " << params.getTolerance() << std::endl;

        QRMethod<std::complex<double>> qr(matrix, params);
        qr.solve();


        std::cout << "\n Results " << std::endl;
        std::cout << "Eigenvalue: \n" << qr.getEigenvalue() << std::endl;
        std::cout << "Eigenvector:\n" <<   qr.getEigenvector() << std::endl;
        std::cout << "Converged? " << (qr.hasConverged() ) << std::endl;
        std::cout << "Iterations: " << qr.getIterationCount()
                  << "/" << params.getMaxIterations() << std::endl;

        auto A = matrix;
        auto v= qr.getEigenvector();
        auto lambda = qr.getEigenvalue();
        auto Av= A* v;
        auto lambda_v= lambda*v;
        auto error= (Av-lambda_v).norm();

        if (error<1e-5) {
            std::cout <<"Test succeed with this error value:"<<error<<std::endl;
            return 0;
        }
        else {
            std::cout <<"Test failed with this error value:"<<error<<std::endl;
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error " << e.what() << std::endl;
        return 1;
    }
    //llms
}

