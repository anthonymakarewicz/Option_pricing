#ifndef CHEBYSHEV_H
#define CHEBYSHEV_H

#include "numerical_analysis/basis_function/base_basis_function.h"

namespace OptionPricer {

    class ChebyshevBasisFunction : public BasisFunction {
    public:
        using BasisFunction::BasisFunction;
        ~ChebyshevBasisFunction() override;

        [[nodiscard]] Eigen::MatrixXd generate(const Eigen::VectorXd& x) const override;
    };

}

#endif //CHEBYSHEV_H
