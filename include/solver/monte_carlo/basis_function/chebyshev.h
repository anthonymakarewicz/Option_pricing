#ifndef CHEBYSHEV_H
#define CHEBYSHEV_H

#include "solver/monte_carlo/basis_function/base_basis_function_strategy.h"

namespace OptionPricer {

    class ChebyshevBasisFunction : public BasisFunctionStrategy {
    public:
        using BasisFunctionStrategy::BasisFunctionStrategy;
        ~ChebyshevBasisFunction() override;

        [[nodiscard]] Eigen::MatrixXd generate(const Eigen::VectorXd& x) const override;
    };

}

#endif //CHEBYSHEV_H
