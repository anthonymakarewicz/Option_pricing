#ifndef MONOMIAL_BASIS_H
#define MONOMIAL_BASIS_H

#include "numerical_analysis/basis_function/base_basis_function.h"

namespace OptionPricer {

    class MonomialBasisFunction final : public BasisFunction {
    public:
        using BasisFunction::BasisFunction;
        ~MonomialBasisFunction() override;

        [[nodiscard]] Eigen::MatrixXd generate(const Eigen::VectorXd &x) const override;
    };
}

#endif //MONOMIAL_BASIS_H
