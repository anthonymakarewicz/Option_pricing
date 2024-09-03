#ifndef BASE_MATRIX_SOLVER_H
#define BASE_MATRIX_SOLVER_H

#include <Eigen/Sparse>
#include <vector>

namespace OptionPricer {

    class BaseMatrixSolver {
    public:
        virtual ~BaseMatrixSolver();

        // Pure virtual method for solving a linear system Ax = b
        virtual Eigen::VectorXd solve(const Eigen::SparseMatrix<double>& A,
                                      const Eigen::VectorXd& b) const = 0;
    };

}

#endif //BASE_MATRIX_SOLVER_H
