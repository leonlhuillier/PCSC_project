#include "TextFileReader.h"
#include "CSVReader.h"
#include <iostream>
#include <cmath>



template <typename Scalar>
using Matrix = Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic>;

template <typename Scalar>
void displayMatrix(const Matrix<Scalar>& matrix) {
    std::cout <<"Matrix ("<< matrix.rows() << "x" << matrix.cols() << ")" << std::endl;
    std::cout <<matrix<<std::endl;
}


void displayParameters(const Parameters& params) {
    std::cout <<"Parameters:\n";
    std::cout <<"Algortihm:" <<params.getAlgorithm()<< "\n";
    std::cout <<"MaxIterations:" <<params.getMaxIterations()<< "\n";
    std::cout <<"Tolerance:" <<params.getTolerance()<< "\n";
    std::cout <<"Shift" <<params.getShift()<< "\n";
}

template <typename Scalar>
bool test_csv_file(const std::string& filename ) {
    std::cout <<"test_csv_file("<< filename << ")" << std::endl;
    try {
        CSVReader<Scalar> reader(filename);
        auto matrix = reader.ReadMatrix();
        displayMatrix(matrix);

        auto parameters = reader.ReadParameters();
        displayParameters(parameters);

        if (matrix.rows() !=3 || matrix.cols() != 3) {
            std::cout << "Wrong matrix size";
            return false;
        }
        if (parameters.getAlgorithm()!="PowerMethod") {
            std::cout << "Wrong algorithm";
            return false;
        }
        if (parameters.getMaxIterations()!=1000) {
            std::cout << "Wrong max iterations";
            return false;
        }
        std::cout <<"CSV test succeed" <<std::endl;
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
}

template <typename Scalar>
bool test_text_file(const std::string& filename ) {
    std::cout <<"test_text_file("<< filename << ")" << std::endl;
    try {
        TextFileReader<Scalar> reader(filename);
        auto matrix = reader.ReadMatrix();
        displayMatrix(matrix);

        auto parameters = reader.ReadParameters();
        displayParameters(parameters);

        if (matrix.rows() !=3 || matrix.cols() != 3) {
            std::cout << "Wrong matrix size";
            return false;
        }
        if (parameters.getAlgorithm()!="PowerMethod") {
            std::cout << "Wrong algorithm";
            return false;
        }
        if (parameters.getMaxIterations()!=1000) {
            std::cout << "Wrong max iterations";
            return false;
        }
        std::cout <<"CSV test succeed" <<std::endl;
        return true;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false; // llms
    }
}


int main() {

    if (test_csv_file<std::complex<double>>("../data/test_matrix.csv")) {
        std::cout <<"Test csv file succeed";
    }

    // Test TXT
    if (test_text_file<double>("../data/test_matrix.txt")){
        std::cout <<"Test text file succeed";
    }

}

