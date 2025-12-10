#include "PowerMethod.h"
#include "ShiftedInversePowerMethod.h"
#include "CSVReader.h"
#include "TextFileReader.h"
#include "Writer.h"
#include "Parameters.h"
#include <iostream>
#include <string>

// ====================================
// FONCTION pour traiter avec double
// ====================================
void runComputationDouble(const std::string& inputFile) {

    //Read Matrix
    Eigen::MatrixXd matrix;
    Parameters params;

    if (inputFile.find(".csv") != std::string::npos) {
        CSVReader<double> reader(inputFile);
        matrix = reader.ReadMatrix();
        params = reader.ReadParameters();
    } else {
        TextFileReader<double> reader(inputFile);
        matrix = reader.ReadMatrix();
        params = reader.ReadParameters();
    }

    std::cout << "\nMatrix size " << matrix.rows() << "x" << matrix.cols() << std::endl;
    std::cout << "\nMatrix:" << std::endl;
    std::cout << matrix << std::endl;

    if (!params.validate()) {
        throw std::runtime_error("Invalid parameters!");
    }

    std::cout << "\nParameters" << std::endl;
    params.display();

    std::string algorithm = params.getAlgorithm();



    // Demander le format de sortie
    std::cout << "  SELECT OUTPUT FORMAT" << std::endl;
    std::cout << "1 - CSV format (.csv)" << std::endl;
    std::cout << "2 - Text format (.txt)" << std::endl;
    std::cout << "\nYour choice [1 or 2]: ";

    int outputChoice;
    std::cin >> outputChoice;

    std::string outputFile;
    Writer* writer = nullptr; //llms

    if (outputChoice == 1) {
        outputFile = "../data/result.csv";
        writer = new CSVWriter(outputFile);
    } else {
        outputFile = "../data/result.txt";
        writer = new TextFileWriter(outputFile);
    }

    if (algorithm == "power" || algorithm == "PowerMethod") {
        PowerMethod<double> pm(matrix, params);
        pm.solve();

        std::cout << "\n Results" << std::endl;
        std::cout << "Eigenvalue: " << pm.getEigenvalue() << std::endl;
        std::cout << "Iterations: " << pm.getIterationCount() << std::endl;
        std::cout << "Converged: " << (pm.hasConverged() ? "Yes" : "No") << std::endl;

        writer->write(pm.getEigenvalue(), pm.getEigenvector(),
                     pm.getIterationCount(), pm.hasConverged());

    } else if (algorithm == "shifted_inverse" || algorithm == "ShiftedInversePowerMethod") {
        ShiftedInversePowerMethod<double> sipm(matrix, params);
        sipm.solve();

        std::cout << "\nResults" << std::endl;
        std::cout << "Eigenvalue: " << sipm.getEigenvalue() << std::endl;
        std::cout << "Iterations: " << sipm.getIterationCount() << std::endl;
        std::cout << "Converged: " << (sipm.hasConverged() ? "Yes" : "No") << std::endl;

        writer->write(sipm.getEigenvalue(), sipm.getEigenvector(),
                     sipm.getIterationCount(), sipm.hasConverged());

    } else {
        delete writer;
        throw std::runtime_error("Unknown algorithm: " + algorithm);
    }

    delete writer;
    std::cout << "\nResults written to: " << outputFile << std::endl;
}

//To treat complex numbers
void runComputationComplex(const std::string& inputFile) {

    // Lire la matrice et les paramètres
    Eigen::MatrixXcd matrix;
    Parameters params;

    if (inputFile.find(".csv") != std::string::npos) {
        CSVReader<std::complex<double>> reader(inputFile);
        matrix = reader.ReadMatrix();
        params = reader.ReadParameters();
    } else {
        TextFileReader<std::complex<double>> reader(inputFile);
        matrix = reader.ReadMatrix();
        params = reader.ReadParameters();
    }

    std::cout << "\nMatrix size: " << matrix.rows() << "x" << matrix.cols() << std::endl;
    std::cout << "\nMatrix:" << std::endl;
    std::cout << matrix << std::endl;

    if (!params.validate()) {
        throw std::runtime_error("Invalid parameters!");
    }

    std::cout << "\nParameters " << std::endl;
    params.display();

    std::string algorithm = params.getAlgorithm();

    // Demander le format de sortie
    std::cout << "  \nSELECT OUTPUT FORMAT" << std::endl;

    std::cout << "1 - CSV format (.csv)" << std::endl;
    std::cout << "2 - Text format (.txt)" << std::endl;
    std::cout << "\nYour choice [1 or 2]: ";

    int outputChoice;
    std::cin >> outputChoice;

    std::string outputFile;
    Writer* writer = nullptr;

    if (outputChoice == 1) {
        outputFile = "../data/result_complex.csv";
        writer = new CSVWriter(outputFile);
    } else {
        outputFile = "../data/result_complex.txt";
        writer = new TextFileWriter(outputFile);
    }

    if (algorithm == "power" || algorithm == "PowerMethod") {
        PowerMethod<std::complex<double>> pm(matrix, params);
        pm.solve();

        std::cout << "\nResults " << std::endl;
        std::cout << "Eigenvalue: " << pm.getEigenvalue() << std::endl;
        std::cout << "Iterations: " << pm.getIterationCount() << std::endl;
        std::cout << "Converged: " << (pm.hasConverged() ? "Yes" : "No") << std::endl;

        writer->write(pm.getEigenvalue(), pm.getEigenvector(),
                     pm.getIterationCount(), pm.hasConverged());

    } else if (algorithm == "shifted_inverse" || algorithm == "ShiftedInversePowerMethod") {
        ShiftedInversePowerMethod<std::complex<double>> sipm(matrix, params);
        sipm.solve();

        std::cout << "\nResults " << std::endl;
        std::cout << "Eigenvalue: " << sipm.getEigenvalue() << std::endl;
        std::cout << "Iterations: " << sipm.getIterationCount() << std::endl;
        std::cout << "Converged: " << (sipm.hasConverged() ? "Yes" : "No") << std::endl;

        writer->write(sipm.getEigenvalue(), sipm.getEigenvector(),
                     sipm.getIterationCount(), sipm.hasConverged());

    } else {
        delete writer;
        throw std::runtime_error("Unknown algorithm: " + algorithm);
    }

    delete writer;
    std::cout << "\nResults written to: " << outputFile << std::endl;
}

// ====================================
// MAIN
// ====================================
int main(int argc, char* argv[]) {
    try {
        std::string inputFile;

        if (argc > 1) {
            inputFile = argv[1];
        } else {
            std::cout << "Enter input file path: ";
            std::cin >> inputFile;
        }



        // Demander le type de données
        std::cout << "  SELECT DATA TYPE" << std::endl;
        std::cout << "1 - Real numbers (double)" << std::endl;
        std::cout << "2 - Complex numbers (complex<double>)" << std::endl;
        std::cout << "\nYour choice [1 or 2]: ";

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            runComputationDouble(inputFile);
        } else if (choice == 2) {
            runComputationComplex(inputFile);
        } else {
            throw std::runtime_error("Invalid choice! Must be 1 or 2.");
        }


        std::cout << "  COMPUTATION COMPLETED SUCCESSFULLY" << std::endl;


    } catch (const std::exception& e) {
        std::cerr << "  ERROR" << std::endl;
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
