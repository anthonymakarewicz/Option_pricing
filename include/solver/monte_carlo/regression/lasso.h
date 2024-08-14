#ifndef LASSO_H
#define LASSO_H

#include "solver/monte_carlo/regression/least_squares.h"

namespace OptionPricer {

    class LassoRegression final: public LeastSquaresRegression {
    public:
        explicit LassoRegression(const double& lambda);
        ~LassoRegression() override;

        [[nodiscard]] Eigen::VectorXd solve(const Eigen::MatrixXd& A, const Eigen::VectorXd& vY) const override;

    private:
        double lambda_;  // Regularization parameter for Ridge
    };

}

#endif //LASSO_H
