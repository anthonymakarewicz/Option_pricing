#ifndef BASE_REGRESSION_STRATEGY_H
#define BASE_REGRESSION_STRATEGY_H

#include <Eigen/Dense>

namespace OptionPricer {

    class Regression {
    public:
        virtual ~Regression();
        [[nodiscard]] virtual Eigen::VectorXd solve(const Eigen::MatrixXd& A, const Eigen::VectorXd& vY) const = 0;
    };

}

#endif //BASE_REGRESSION_STRATEGY_H
