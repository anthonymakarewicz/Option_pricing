#ifndef LEAST_SQUARES_H
#define LEAST_SQUARES_H

#include "solver/monte_carlo/regression/base_regression_strategy.h"

namespace OptionPricer {

    class LeastSquaresRegression: public RegressionStrategy {
    public:
        ~LeastSquaresRegression() override;
        [[nodiscard]] Eigen::VectorXd solve(const Eigen::MatrixXd& A, const Eigen::VectorXd& vY) const override;
    };

}

#endif //LEAST_SQUARES_H
