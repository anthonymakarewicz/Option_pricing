#include "numerical_analysis/linear_algebra/matrix_solver/thomas_algorithm.h"

namespace OptionPricer {

    Eigen::VectorXd ThomasAlgorithm::solve(const Eigen::SparseMatrix<double> &A, const Eigen::VectorXd &b) const {
        const size_t n = A.rows();
        if (n < 2)
            throw std::invalid_argument("Matrix size must be at least 2x2 for Thomas Algorithm.");

        // Extracting the tridiagonal coefficients from the sparse matrix A
        std::vector<double> a(n-1), bDiag(n), c(n-1);
        for (size_t i = 0; i < n-1; ++i) {
            a[i] = A.coeff(i+1, i);
            c[i] = A.coeff(i, i+1);
        }
        for (size_t i = 0; i < n; ++i) {
            bDiag[i] = A.coeff(i, i);
        }

        // Forward sweep
        std::vector<double> cStar(n-1), dStar(n);
        cStar[0] = c[0] / bDiag[0];
        dStar[0] = b[0] / bDiag[0];

        for (size_t i = 1; i < n-1; ++i) {
            const double m = bDiag[i] - a[i-1] * cStar[i-1];
            cStar[i] = c[i] / m;
            dStar[i] = (b[i] - a[i-1] * dStar[i-1]) / m;
        }
        dStar[n-1] = (b[n-1] - a[n-2] * dStar[n-2]) /
                  (bDiag[n-1] - a[n-2] * cStar[n-2]);

        // Back substitution
        Eigen::VectorXd x(n);
        x(n-1) = dStar[n-1];
        for (int i = n-2; i >= 0; --i) {
            x[i] = dStar[i] - cStar[i] * x[i+1];
        }

        return x;
    }

}
