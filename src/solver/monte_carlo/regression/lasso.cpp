#include "solver/monte_carlo/regression/lasso.h"

namespace OptionPricer {

    LassoRegression::LassoRegression(const double &lambda)
    : lambda_(lambda) {
        if (lambda_ < 0) throw std::invalid_argument("Regularization parameter lambda must be non-negative");
    }

    LassoRegression::~LassoRegression() = default;

    Eigen::VectorXd LassoRegression::solve(const Eigen::MatrixXd &A, const Eigen::VectorXd &vY) const {
        const Eigen::VectorXd betaLS = LeastSquaresRegression::solve(A, vY);
        return betaLS.unaryExpr([this](const double& beta_i) {
            // Soft thresholding function
            return std::max(0.0, beta_i - lambda_) - std::max(0.0, -beta_i - lambda_);
        });
    }

}
