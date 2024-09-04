#ifndef BASE_BASIS_FUNCTION_H
#define BASE_BASIS_FUNCTION_H

#include <Eigen/Dense>

namespace OptionPricer {

    class BasisFunction {
    public:
        explicit BasisFunction(const unsigned int& numberBasis);
        virtual ~BasisFunction();

        [[nodiscard]] virtual Eigen::MatrixXd generate(const Eigen::VectorXd& x) const = 0;

    protected:
        unsigned int numberBasis_; // Number of basis functions to generate
    };

}

#endif //BASE_BASIS_FUNCTION_H
