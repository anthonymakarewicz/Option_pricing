#ifndef BASE_REGRESSION_STRATEGY_H
#define BASE_REGRESSION_STRATEGY_H

#include "Eigen/Dense"

namespace OptionPricer {

    class RegressionStrategy {
    public:
        virtual ~RegressionStrategy();
        [[nodiscard]] virtual Eigen::VectorXd solve(const Eigen::MatrixXd& A, const Eigen::VectorXd& vY) const = 0;
    };

}

#endif //BASE_REGRESSION_STRATEGY_H
