//
// Created by 32484 on 05-12-25.
//
//
// Created by fanni on 05/12/2025.
//
#include "Reader.h"
#include <iostream>
#include <string>
#include <fstream>
template<typename Scalar>
// Constructor
Reader<Scalar>::Reader(const std::string& fileName):mFilename(fileName),mFileType(FileType::UNKNOWN) {
    std::ifstream file(mFilename);
    if (!file.good()) {
        throw std::runtime_error("File not found"); //check if the file exist
    }
    file.close();

    if (mFilename.find(".csv")!=std::string::npos) {
        //npos check if he found something
        mFileType= FileType::CSV ;
    }

    else if (mFilename.find(".txt") != std::string::npos ||
             mFilename.find(".dat") != std::string::npos) {
        mFileType = FileType::TEXT;
             }
    else {
        mFileType = FileType::UNKNOWN;
        throw std::runtime_error ("Unknown file type" + mFilename);
    }
    std::cout << "File :" << mFilename << "| Type: " <<GetFileTypeString() << std::endl;

    }


// Destructor
template<typename Scalar>
Reader<Scalar>::~Reader(){}

template<typename Scalar>
// Get file type
typename Reader<Scalar>::FileType Reader<Scalar>::GetFileType() const {
    return mFileType;
}

template<typename Scalar>
std::string Reader<Scalar>::GetFileTypeString() const {
    if (mFileType == FileType::CSV) return "CSV";
    if (mFileType == FileType::TEXT) return "TEXT";
    return "UNKNOWN";

}
template class Reader<double>;
template class Reader<std::complex<double>>;

//
