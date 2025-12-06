//
// Created by 32484 on 05-12-25.
//
#include "CSVReader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "Reader.h"


//constructor
template<typename Scalar>
CSVReader<Scalar>::CSVReader(const std::string &filename)
    :Reader<Scalar>(filename)
{
    if (this->GetFileType()!= Reader<Scalar>::FileType::CSV) {
        throw std::runtime_error( "This file is not a CSV file" );
    }

    std::cout << "CSV file :" << filename << std::endl;
}

//Destrucor
template<typename Scalar>
CSVReader<Scalar>::~CSVReader() {}



//Pour qu'il prend pas en compte les espaces vide dans les fichiers
template<typename Scalar>
std::string CSVReader<Scalar>::trim(const std::string& str) { //llms
    if (str.empty()) return str; //Si la chaîne est vide, on la retourne directement

    // Find first non-space
    int start = 0;
    while (start < str.length() && std::isspace(str[start])) { //On cherche le premier caractère qui n’est pas un espace
        start++;
    }

    // Find last non-space
    int end = str.length() - 1;
    while (end >= start && std::isspace(str[end])) { //On cherche le dernier caractère non-espace
        end--;
    }

    // Return trimmed string
    return str.substr(start, end - start + 1);
}

template<typename Scalar>
typename CSVReader<Scalar>::Matrix CSVReader<Scalar>::ReadMatrix() {
    std::ifstream file(this->mFilename);
    if (!file.is_open()) {
        throw std::runtime_error("Opening CSV file failed");
    }
    std::vector<std::vector<double>> matrixData;
    std::string line;

    while (std::getline(file, line)){
        line=trim(line); //remove whitespace
        if (line.empty()) continue;

        if (line.find("Algorithm") != std::string::npos) {
            break;  //  Stop because the parameters begin
        }


        //Pour chaque ligne, on découpe avec la virgule , et on convertit chaque morceau en double, pour recuperer les lignes de la matric
        std::vector<double> row;
        std::stringstream ss(line);
        std::string value;

        while (std::getline(ss, value, ',')) {
            value=trim(value); //enlever espaces entre les nombres
            row.push_back(std::stod(value));
        }

        matrixData.push_back(row);
    }

    file.close();
    // Convert vector to Eigen matrix
    if (matrixData.empty()) {
        throw std::runtime_error("No matrix found in CSV file");
    }

    int n = matrixData.size();
    int m = matrixData[0].size();

    Matrix matrix(n, m);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            matrix(i, j) = static_cast<Scalar>(matrixData[i][j]); //llms
        }
    }

    return matrix;
}

template<typename Scalar>
Parameters CSVReader<Scalar>::ReadParameters() {
    std::ifstream file(this->mFilename);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file");
    }

    Parameters params;
    std::string line;

    // Skip until "Algorithm" line
    while (std::getline(file, line)) {
        if (line.find("Algorithm") != std::string::npos) {
            // Process this line first
            std::stringstream ss(line);
            std::string name, value;
            std::getline(ss, name, ',');
            std::getline(ss, value);
            params.setAlgorithm(value);
            break;
        }
    }

    // Read remaining parameters
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string name, value;

        std::getline(ss, name, ',');
        std::getline(ss, value);

        if (name == "MaxIterations") {
            params.setMaxIterations(std::stoi(value));
        }
        else if (name == "Tolerance") {
            params.setTolerance(std::stod(value));
        }
        else if (name == "Shift") {
            params.setShift(std::stod(value));
        }
    }

    file.close();
    return params;

}
template class CSVReader<double>;
template class CSVReader<std::complex<double>>;








