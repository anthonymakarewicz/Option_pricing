#include "solver/monte_carlo/basis_function/base_basis_function_strategy.h"

namespace OptionPricer {

    BasisFunctionStrategy::BasisFunctionStrategy(const unsigned int &numberBasis)
    : numberBasis_(numberBasis) {
        if (numberBasis_ <= 0) throw std::invalid_argument("Number of basis functions must be positive");
    }

    BasisFunctionStrategy::~BasisFunctionStrategy() = default;

}
