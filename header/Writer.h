#ifndef WRITER_H
#define WRITER_H

#include <string>
#include <complex>
#include <Eigen/Dense>


class Writer {
protected:
    std::string mFilename;

public:
    Writer(const std::string& filename);

    virtual ~Writer() = default;


    virtual void write(double eigenvalue,
                      const Eigen::VectorXd& eigenvector,
                      int iterations,
                      bool converged) const = 0;

    virtual void write(std::complex<double> eigenvalue,
                      const Eigen::VectorXcd& eigenvector,
                      int iterations,
                      bool converged) const = 0;

    virtual void writeAll(const Eigen::VectorXd& eigenvalues,
                         const Eigen::MatrixXd& eigenvectors,
                         int iterations,
                         bool converged) const = 0;

    virtual void writeAll(const Eigen::VectorXcd& eigenvalues,
                         const Eigen::MatrixXcd& eigenvectors,
                         int iterations,
                         bool converged) const = 0;
};


class CSVWriter : public Writer {
public:
    CSVWriter(const std::string& filename);

    void write(double eigenvalue,
              const Eigen::VectorXd& eigenvector,
              int iterations,
              bool converged) const override;

    void write(std::complex<double> eigenvalue,
              const Eigen::VectorXcd& eigenvector,
              int iterations,
              bool converged) const override;

    void writeAll(const Eigen::VectorXd& eigenvalues,
                 const Eigen::MatrixXd& eigenvectors,
                 int iterations,
                 bool converged) const override;

    void writeAll(const Eigen::VectorXcd& eigenvalues,
                 const Eigen::MatrixXcd& eigenvectors,
                 int iterations,
                 bool converged) const override;
};

class TextFileWriter : public Writer {
public:
    TextFileWriter(const std::string& filename);

    void write(double eigenvalue,
              const Eigen::VectorXd& eigenvector,
              int iterations,
              bool converged) const override;

    void write(std::complex<double> eigenvalue,
              const Eigen::VectorXcd& eigenvector,
              int iterations,
              bool converged) const override;

    void writeAll(const Eigen::VectorXd& eigenvalues,
                 const Eigen::MatrixXd& eigenvectors,
                 int iterations,
                 bool converged) const override;

    void writeAll(const Eigen::VectorXcd& eigenvalues,
                 const Eigen::MatrixXcd& eigenvectors,
                 int iterations,
                 bool converged) const override;
};

#endif // WRITER_H
