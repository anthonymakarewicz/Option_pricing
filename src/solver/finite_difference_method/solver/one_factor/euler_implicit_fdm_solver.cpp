#include "solver/finite_difference_method/solver/one_factor/euler_implicit_fdm_solver.h"
#include "numerical_analysis/linear_algebra/matrix_solver/lu_decomposition.h"
#include <iostream>

namespace OptionPricer::FDM::OneFactor {

    EulerImplicitFDM::EulerImplicitFDM(const double &xDom, const unsigned long &J,
                                       const double &tDom, const unsigned long &N,
                                       std::unique_ptr<ConvectionDiffusionPDE> pde,
                                       std::shared_ptr<EuropeanOption> option,
                                       std::shared_ptr<IMarketData> marketData,
                                       std::shared_ptr<Interpolation> interpolation,
                                       std::shared_ptr<MatrixSolver> matrixSolver)
    : FDMSolver(xDom, J, tDom, N, std::move(pde), std::move(option), std::move(marketData), std::move(interpolation)) {
        if (!matrixSolver)
            matrixSolver_ = std::make_shared<LUDecompositionSolver>();
        else
            matrixSolver_ = std::move(matrixSolver);

        A.resize(J_-2, J_-2);
        b.resize(J_-2);
    }

    EulerImplicitFDM::~EulerImplicitFDM() = default;

    void EulerImplicitFDM::calculateBoundaryConditions() {
        newPrices.front() = pde_->boundaryLeft(tCurr, xValues.front());
        newPrices.back() = pde_->boundaryRight(tCurr, xValues.back());
    }

    void EulerImplicitFDM::calculateInnerDomain() {
        std::vector<Eigen::Triplet<double>> tripletList;
        tripletList.reserve(3 * (J_-2));  // Preallocate space for diagonal elements

        for (unsigned long j = 1; j < (J_-1); ++j) {
            const double dtSig = dt * pde_->diffusion(tCurr, xValues[j]);
            const double dtSig2 = 0.5 * dt * dx * pde_->convection(tCurr, xValues[j]);

            // Differencing coefficients
            alpha = dtSig - dtSig2;
            beta = -dx2 - 2.0 * dtSig + dt * dx2 * pde_->reaction(tCurr, xValues[j]);
            gamma = dtSig + dtSig2;

            // Diagonal dominance check
            if (std::abs(beta) < std::abs(alpha) + std::abs(gamma)) {
                std::cerr << "Warning: Matrix is not diagonally dominant at row " << j
                          << ". This may lead to numerical instability." << std::endl;
            }

            // Fill in the tridiagonal matrix
            if (j > 1) {
                tripletList.emplace_back(j-1, j-2, alpha);    // Lower diagonal
            }
            tripletList.emplace_back(j-1, j-1, beta);       // Main diagonal
            if (j < J_-2) {
                tripletList.emplace_back(j-1, j, gamma);  // Upper diagonal
            }

            // RHS vector
            b[j-1] = dx2 * (dt * pde_->rightHandSide(tCurr, xValues[j]) - oldPrices[j]);
            if (j == 1)
                b[0] -= alpha * newPrices[0];         // Adjust for the boundary condition on the left
            if (j == J_-2)
                b[J_-3] -= gamma * newPrices[J_-1]; // Adjust for the boundary condition on the right
        }

        // Solve for the matrix system
        A.setFromTriplets(tripletList.begin(), tripletList.end());
        Eigen::VectorXd solution = matrixSolver_->solve(A, b);

        // Copy the solution to the internal prices
        for (unsigned long j = 1; j < (J_-1); ++j) {
            newPrices[j] = solution[j-1];
        }
    }

}
