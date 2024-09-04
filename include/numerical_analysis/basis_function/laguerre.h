#ifndef LAGUERRE_H
#define LAGUERRE_H

#include "numerical_analysis/basis_function/base_basis_function.h"

namespace OptionPricer {

    class LaguerreBasisFunction final : public BasisFunction {
    public:
        using BasisFunction::BasisFunction;
        ~LaguerreBasisFunction() override;

        [[nodiscard]] Eigen::MatrixXd generate(const Eigen::VectorXd& x) const override;
    };

}

#endif //LAGUERRE_H
