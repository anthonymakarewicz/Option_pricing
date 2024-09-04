#ifndef THOMAS_ALGORITHM_H
#define THOMAS_ALGORITHM_H

#include "base_matrix_solver.h"

namespace OptionPricer {

    class ThomasAlgorithm final : public MatrixSolver {
    public:
        Eigen::VectorXd solve(const Eigen::SparseMatrix<double>& A,
                              const Eigen::VectorXd& b) const override;
    };

}

#endif //THOMAS_ALGORITHM_H
