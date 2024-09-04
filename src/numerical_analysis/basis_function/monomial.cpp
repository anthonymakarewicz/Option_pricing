#include "numerical_analysis/basis_function/monomial.h"

namespace OptionPricer {

    MonomialBasisFunction::~MonomialBasisFunction() = default;

    Eigen::MatrixXd MonomialBasisFunction::generate(const Eigen::VectorXd &x) const {
        Eigen::MatrixXd A(x.size(), numberBasis_);
        for (int n = 0; n < numberBasis_; ++n) {
            A.col(n) = x.array().pow(n); // x^n
        }
        return A;
    }

}
