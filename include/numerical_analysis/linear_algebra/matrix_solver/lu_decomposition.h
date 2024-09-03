#ifndef LU_DECOMPOSITION_H
#define LU_DECOMPOSITION_H

#include "base_matrix_solver.h"

namespace OptionPricer {

    class LUDecompositionSolver final : public BaseMatrixSolver {
    public:
        Eigen::VectorXd solve(const Eigen::SparseMatrix<double>& A,
                              const Eigen::VectorXd& b) const override;
    };

}

#endif //LU_DECOMPOSITION_H
