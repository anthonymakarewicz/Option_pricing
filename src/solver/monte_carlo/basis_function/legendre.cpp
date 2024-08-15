#include "solver/monte_carlo/basis_function/legendre.h"

namespace OptionPricer {

    LegendreBasisFunction::~LegendreBasisFunction() = default;

    Eigen::MatrixXd LegendreBasisFunction::generate(const Eigen::VectorXd &x) const {
        Eigen::MatrixXd basis(x.size(), numberBasis_);
        basis.col(0).setOnes(); // P0(x) = 1

        if (numberBasis_ > 1)
            basis.col(1) = x; // P1(x) = x

        for (int n = 2; n < numberBasis_; ++n) {
            basis.col(n) = ((2*(n-1) + 1) * x.array() * basis.col(n-1).array()
                - (n-1)*basis.col(n-2).array()) / n;
        }

        return basis;
    }

}
