#ifndef LEAST_SQUARES_H
#define LEAST_SQUARES_H

#include "numerical_analysis/regression/base_regression.h"

namespace OptionPricer {

    class LeastSquaresRegression: public Regression {
    public:
        ~LeastSquaresRegression() override;
        [[nodiscard]] Eigen::VectorXd solve(const Eigen::MatrixXd& A, const Eigen::VectorXd& vY) const override;
    };

}

#endif //LEAST_SQUARES_H
