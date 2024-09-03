#ifndef EULER_IMPLICIT_FDM_SOLVER_H
#define EULER_IMPLICIT_FDM_SOLVER_H

#include "market_data/interface_market_data.h"
#include "option/single_path/european_option.h"
#include "numerical_analysis/interpolation/base_interpolation.h"
#include "solver/finite_difference_method/pde/one_factor/base_convection_diffusion_pde.h"
#include "solver/finite_difference_method/solver/one_factor/base_fdm_solver.h"
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <numerical_analysis/linear_algebra/matrix_solver/base_matrix_solver.h>

namespace OptionPricer::FDM::OneFactor {

    using namespace PDE::OneFactor;

    class EulerImplicitFDM final : public FDMSolver {
    public:
        EulerImplicitFDM(const double &xDom, const unsigned long &J,
                         const double &tDom, const unsigned long &N,
                         std::unique_ptr<ConvectionDiffusionPDE> pde,
                         std::shared_ptr<EuropeanOption> option,
                         std::shared_ptr<IMarketData> marketData,
                         std::shared_ptr<Interpolation> interpolation = nullptr,
                         std::shared_ptr<BaseMatrixSolver> matrixSolver = nullptr);

        ~EulerImplicitFDM() override;

    private:
        void calculateInnerDomain() override;

        std::shared_ptr<BaseMatrixSolver> matrixSolver_;
        double alpha, beta, gamma;       // Differencing coefficients
        Eigen::SparseMatrix<double> A;  // Coefficient matrix
        Eigen::VectorXd b;             // Right-hand side vector
    };

}

#endif //EULER_IMPLICIT_FDM_SOLVER_H
