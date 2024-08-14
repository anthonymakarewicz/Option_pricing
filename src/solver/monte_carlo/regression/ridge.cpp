#include "solver/monte_carlo/regression/ridge.h"

namespace OptionPricer {

    RidgeRegression::RidgeRegression(const double &lambda)
    : lambda_(lambda) {
        if (lambda_ < 0) throw std::invalid_argument("Regularization parameter lambda must be non-negative");
    }

    RidgeRegression::~RidgeRegression() = default;

    Eigen::VectorXd RidgeRegression::solve(const Eigen::MatrixXd &A, const Eigen::VectorXd &vY) const {
        const int numBasisFunctions = A.cols();
        const Eigen::MatrixXd I = Eigen::MatrixXd::Identity(numBasisFunctions, numBasisFunctions);
        return (A.transpose() * A + lambda_ * I).ldlt().solve(A.transpose() * vY);
    }

}
