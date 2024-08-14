#ifndef BASE_BASIS_FUNCTION_H
#define BASE_BASIS_FUNCTION_H

#include <Eigen/Dense>

namespace OptionPricer {

    class BasisFunctionStrategy {
    public:
        explicit BasisFunctionStrategy(const unsigned int& numberBasis);
        virtual ~BasisFunctionStrategy();

        [[nodiscard]] virtual Eigen::MatrixXd generate(const Eigen::VectorXd& x) const = 0;

    protected:
        unsigned int numberBasis_; // Number of basis functions to generate
    };

}

#endif //BASE_BASIS_FUNCTION_H
