#ifndef EIGENVALUE_H
#define EIGENVALUE_H

#include <Eigen/Dense>
#include <string>

class Eigenvalue {
public:
    // Constructors and Destructor
    Eigenvalue();
    virtual ~Eigenvalue();

    // Public Methods
    virtual void solve() = 0;
    void setTolerance(double tolerance);
    void setMaxIteration(int maxIteration);
    bool hasConverged() const;
    double getEigenvalue() const;
    double getTolerance() const;
    int getMaxIteration() const;
    Eigen::VectorXd getEigenvector() const;

    // Loading Methods
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename);

protected:
    // Protected Member Variables
    Eigen::MatrixXd mMatrix;
    Eigen::VectorXd mEigenvector;
    double mEigenvalue;
    int mMaxIteration;
    double mTolerance;
};

#endif //EIGENVALUE_H
