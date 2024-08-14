#ifndef LEGENDRE_H
#define LEGENDRE_H

#include "solver/monte_carlo/basis_function/base_basis_function_strategy.h"

namespace OptionPricer {

    class LegendreBasisFunction final : public BasisFunctionStrategy {
    public:
        using BasisFunctionStrategy::BasisFunctionStrategy;
        ~LegendreBasisFunction() override;

        [[nodiscard]] Eigen::MatrixXd generate(const Eigen::VectorXd& x) const override;
    };

}

#endif //LEGENDRE_H
