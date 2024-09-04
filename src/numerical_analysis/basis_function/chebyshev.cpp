#include "numerical_analysis/basis_function/chebyshev.h"

namespace OptionPricer {

    ChebyshevBasisFunction::~ChebyshevBasisFunction() = default;

    Eigen::MatrixXd ChebyshevBasisFunction::generate(const Eigen::VectorXd &x) const {
        Eigen::MatrixXd basis(x.size(), numberBasis_);
        basis.col(0).setOnes(); // T0(x) = 1

        if (numberBasis_ > 1) {
            basis.col(1) = x; // T1(x) = x
        }

        for (int n = 2; n < numberBasis_; ++n) {
            basis.col(n) = 2 * x.array() * basis.col(n-1).array() - basis.col(n-2).array();
        }

        return basis;
    }

}
