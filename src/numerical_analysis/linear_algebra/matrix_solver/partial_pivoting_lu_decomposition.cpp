#include "numerical_analysis/linear_algebra/matrix_solver/partial_pivoting_lu_decomposition.h"
#include <Eigen/Dense>

namespace OptionPricer {

    Eigen::VectorXd PartialPivotingLUSolver::solve(const Eigen::SparseMatrix<double> &A,
                                                    const Eigen::VectorXd &b) const {
        // Convert the sparse matrix A to a dense matrix for LU decomposition
        Eigen::MatrixXd denseA = Eigen::MatrixXd(A);

        // Perform LU decomposition with partial pivoting
        Eigen::PartialPivLU<Eigen::MatrixXd> lu(denseA);

        // Solve the system Ax = b
        Eigen::VectorXd solution = lu.solve(b);

        return solution;
    }

}
