#ifndef LAGUERRE_H
#define LAGUERRE_H

#include "solver/monte_carlo/basis_function/base_basis_function_strategy.h"

namespace OptionPricer {

    class LaguerreBasisFunction final : public BasisFunctionStrategy {
    public:
        using BasisFunctionStrategy::BasisFunctionStrategy;
        ~LaguerreBasisFunction() override;

        [[nodiscard]] Eigen::MatrixXd generate(const Eigen::VectorXd& x) const override;
    };

}

#endif //LAGUERRE_H
