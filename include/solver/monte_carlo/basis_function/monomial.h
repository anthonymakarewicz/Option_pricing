#ifndef MONOMIAL_BASIS_H
#define MONOMIAL_BASIS_H

#include "solver/monte_carlo/basis_function/base_basis_function_strategy.h"

namespace OptionPricer {

    class MonomialBasisFunction final : public BasisFunctionStrategy {
    public:
        using BasisFunctionStrategy::BasisFunctionStrategy;
        ~MonomialBasisFunction() override;

        [[nodiscard]] Eigen::MatrixXd generate(const Eigen::VectorXd &x) const override;
    };
}

#endif //MONOMIAL_BASIS_H
