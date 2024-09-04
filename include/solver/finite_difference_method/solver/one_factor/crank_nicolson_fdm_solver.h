#ifndef CRANK_NICOLSON_FDM_SOLVER_H
#define CRANK_NICOLSON_FDM_SOLVER_H

#include <numerical_analysis/linear_algebra/matrix_solver/base_matrix_solver.h>
#include "solver/finite_difference_method/solver/one_factor/base_fdm_solver.h"

namespace OptionPricer::FDM::OneFactor {

    using namespace PDE::OneFactor;

    class CrankNicolsonFDMSolver final : public FDMSolver {
    public:
        CrankNicolsonFDMSolver(const double &xDom, const unsigned long &J,
                               const double &tDom, const unsigned long &N,
                               std::unique_ptr<ConvectionDiffusionPDE> pde,
                               std::shared_ptr<EuropeanOption> option,
                               std::shared_ptr<IMarketData> marketData,
                               std::shared_ptr<Interpolation> interpolation = nullptr,
                               std::shared_ptr<MatrixSolver> matrixSolver = nullptr);

        ~CrankNicolsonFDMSolver() override;

    private:
        void calculateInnerDomain() override;
        void calculateBoundaryConditions() override;

        std::shared_ptr<MatrixSolver> matrixSolver_;
        double alpha, beta, gamma;       // Differencing coefficients
        Eigen::SparseMatrix<double> A;  // Coefficient matrix for the implicit part
        Eigen::VectorXd b;             // Right-hand side vector
    };

}

#endif // CRANK_NICOLSON_FDM_SOLVER_H