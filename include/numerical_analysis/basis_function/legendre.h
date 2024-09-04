#ifndef LEGENDRE_H
#define LEGENDRE_H

#include "numerical_analysis/basis_function/base_basis_function.h"

namespace OptionPricer {

    class LegendreBasisFunction final : public BasisFunction {
    public:
        using BasisFunction::BasisFunction;
        ~LegendreBasisFunction() override;

        [[nodiscard]] Eigen::MatrixXd generate(const Eigen::VectorXd& x) const override;
    };

}

#endif //LEGENDRE_H
