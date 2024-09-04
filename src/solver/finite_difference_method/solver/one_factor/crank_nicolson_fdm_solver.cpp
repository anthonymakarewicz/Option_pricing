#include "solver/finite_difference_method/solver/one_factor/crank_nicolson_fdm_solver.h"
#include "numerical_analysis/linear_algebra/matrix_solver/lu_decomposition.h"
#include <iostream>

namespace OptionPricer::FDM::OneFactor {

    CrankNicolsonFDMSolver::CrankNicolsonFDMSolver(const double &xDom, const unsigned long &J,
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

    CrankNicolsonFDMSolver::~CrankNicolsonFDMSolver() = default;

    void CrankNicolsonFDMSolver::calculateBoundaryConditions() {
        newPrices.front() = pde_->boundaryLeft(tCurr, xValues.front());
        newPrices.back() = pde_->boundaryRight(tCurr, xValues.back());
    }

    void CrankNicolsonFDMSolver::calculateInnerDomain() {
        std::vector<Eigen::Triplet<double>> tripletListA;
        std::vector<Eigen::Triplet<double>> tripletListB;
        tripletListA.reserve(3 * (J_-2));   // Preallocate space for diagonal elements of A
        //tripletListB.reserve(3 * (J_-2));  // Preallocate space for diagonal elements of B

        double dtSig = 0.0, dtSig2 = 0.0, reaction = 0.0; // Temporary variables
        for (unsigned long j = 1; j < (J_-1); ++j) {

            // Coefficients for the current time step (tCurr)
            dtSig = dt * pde_->diffusion(tCurr, xValues[j]);
            dtSig2 = 0.5 * dt * dx * pde_->convection(tCurr, xValues[j]);
            reaction = 0.5 * dt * dx2 * pde_->reaction(tCurr, xValues[j]);

            alpha = 0.5 * (dtSig - dtSig2);    // LHS (implicit) lower diagonal
            beta = -dx2 - dtSig + reaction;   // LHS (implicit) main diagonal
            gamma = 0.5 * (dtSig + dtSig2);  // LHS (implicit) upper diagonal

            // Diagonal dominance check
            if (std::abs(beta) < std::abs(alpha) + std::abs(gamma)) {
                std::cerr << "Warning: Matrix is not diagonally dominant at row " << j
                          << ". This may lead to numerical instability." << std::endl;
            }

            // Fill A matrix (implicit part) for the current time step
            if (j > 1) {
                tripletListA.emplace_back(j-1, j-2, alpha);    // Lower diagonal
            }
            tripletListA.emplace_back(j-1, j-1, beta);       // Main diagonal
            if (j < J_-2) {
                tripletListA.emplace_back(j-1, j, gamma);  // Upper diagonal
            }

            // RHS vector b
            b[j-1] = 0.5 * dx2*dt * (pde_->rightHandSide(tCurr, xValues[j]) + pde_->rightHandSide(tPrev, xValues[j]));

            // Adjust for the boundary conditions
            if (j == 1) {
                b[0] -= alpha * newPrices[0];
            }
            if (j == J_-2) {
                b[J_-3] -= gamma * newPrices[J_-1];
            }

            // Coefficients for the previous time step (tPrev)
            dtSig = dt * pde_->diffusion(tPrev, xValues[j]);
            dtSig2 = 0.5 * dt*dx * pde_->convection(tPrev, xValues[j]);
            reaction = 0.5 * dt*dx2 * pde_->reaction(tPrev, xValues[j]);

            alpha = -0.5 * (dtSig - dtSig2);    // RHS (explicit) lower diagonal
            beta = -dx2 + dtSig - reaction;    // RHS (explicit) main diagonal
            gamma = -0.5 * (dtSig + dtSig2);  // RHS (explicit) upper diagonal

            // Add the explicit part
            b[j-1] += beta * oldPrices[j];
            if (j > 1) {
                b[j-1] += alpha * oldPrices[j-1];
            }
            if (j < J_-2) {
                b[j-1] += gamma * oldPrices[j+1];
            }

            // Convert triplets to sparse matrices
            A.setFromTriplets(tripletListA.begin(), tripletListA.end());

            // Solve for the matrix system A * newPrices = b
            Eigen::VectorXd solution = matrixSolver_->solve(A, b);

            // Copy the solution to the internal prices
            for (unsigned long j = 1; j < (J_-1); ++j) {
                newPrices[j] = solution[j-1];
            }
        }
    }

}
