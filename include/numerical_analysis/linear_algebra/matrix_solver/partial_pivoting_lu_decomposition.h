#ifndef PARTIAL_PIVOTING_LU_DECOMPOSITION_H
#define PARTIAL_PIVOTING_LU_DECOMPOSITION_H

#include "base_matrix_solver.h"

namespace OptionPricer {

    class PartialPivotingLUSolver : public MatrixSolver {
    public:
        Eigen::VectorXd solve(const Eigen::SparseMatrix<double>& A,
                              const Eigen::VectorXd& b) const override;
    };

}

#endif //PARTIAL_PIVOTING_LU_DECOMPOSITION_H
