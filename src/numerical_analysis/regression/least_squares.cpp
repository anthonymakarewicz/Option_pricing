#include "numerical_analysis/regression/least_squares.h"

namespace OptionPricer {

    LeastSquaresRegression::~LeastSquaresRegression() = default;

    Eigen::VectorXd LeastSquaresRegression::solve(const Eigen::MatrixXd &A, const Eigen::VectorXd &vY) const {
        return A.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(vY);
    }

}
