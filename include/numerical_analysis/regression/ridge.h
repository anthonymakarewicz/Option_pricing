#ifndef RIDGE_H
#define RIDGE_H

#include "numerical_analysis/regression/least_squares.h"

namespace OptionPricer {

    class RidgeRegression final: public LeastSquaresRegression {
    public:
        explicit RidgeRegression(const double& lambda);
        ~RidgeRegression() override;

        [[nodiscard]] Eigen::VectorXd solve(const Eigen::MatrixXd& A, const Eigen::VectorXd& vY) const override;

    private:
        double lambda_;  // Regularization parameter for Ridge
    };

}

#endif //RIDGE_H
