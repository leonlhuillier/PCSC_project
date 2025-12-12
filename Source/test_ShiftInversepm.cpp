//
// Created by fanni on 10/12/2025.
//
//
// Created by fanni on 10/12/2025.
//

#include "TextFileReader.h"
#include "ShiftedInversePowerMethod.h"

int main() {
    try {
        TextFileReader<> reader("../data/test_matrix_shift.txt");
        auto matrix=reader.ReadMatrix();

        std::cout <<" Matrix:\n"<< matrix<<"\n" << std::endl;
        Parameters params=reader.ReadParameters();


        std::cout << "Max iterations: " << params.getMaxIterations() << std::endl;
        std::cout << "Tolerance: " << params.getTolerance() << std::endl;

        ShiftedInversePowerMethod<double> spm(matrix, params);
        spm.solve();


        std::cout << "\n Results " << std::endl;
        std::cout << "Eigenvalue: \n" << spm.getEigenvalue() << std::endl;
        std::cout << "Eigenvector:\n" << spm.getEigenvector() << std::endl;
        std::cout << "Converged? " << (spm.hasConverged() ) << std::endl;
        std::cout << "Iterations: " << spm.getIterationCount()
                  << "/" << params.getMaxIterations() << std::endl;

        auto A = matrix;
        auto v= spm.getEigenvector();
        auto lambda = spm.getEigenvalue();
        auto Av= A* v;
        auto lambda_v= lambda*v;
        auto error= (Av-lambda_v).norm();

        if (error<1e-5) {
            std::cout <<"Test succeed with this error value="<<error<<std::endl;
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
}

