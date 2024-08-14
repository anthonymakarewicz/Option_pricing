#include "solver/monte_carlo/basis_function/laguerre.h"

namespace OptionPricer {

    LaguerreBasisFunction::~LaguerreBasisFunction() = default;

    Eigen::MatrixXd LaguerreBasisFunction::generate(const Eigen::VectorXd &x) const {
        Eigen::MatrixXd basis(x.size(), numberBasis_);
        basis.col(0).setOnes(); // L0(x) = 1

        if (numberBasis_ > 1) {
            basis.col(1) = 1.0 - x.array(); // L1(x) = 1 - x
        }

        for (int n = 2; n < numberBasis_; ++n) {
            basis.col(n) = ((2 * n - 1 - x.array()) * basis.col(n-1).array()
                            - (n - 1) * basis.col(n-2).array()) / n;
        }

        return basis;
    }

}
