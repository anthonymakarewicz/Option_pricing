#include "numerical_analysis/linear_algebra/matrix_solver/lu_decomposition.h"
#include <Eigen/SparseLU>

namespace OptionPricer {

    Eigen::VectorXd LUDecompositionSolver::solve(const Eigen::SparseMatrix<double> &A, const Eigen::VectorXd &b) const {
        Eigen::SparseLU<Eigen::SparseMatrix<double>> solver;
        solver.compute(A);

        if (solver.info() != Eigen::Success) {
            throw std::runtime_error("LU decomposition failed!");
        }

        Eigen::VectorXd solution = solver.solve(b);
        if (solver.info() != Eigen::Success) {
            throw std::runtime_error("Solving the linear system failed!");
        }

        return solution;
    }

}
