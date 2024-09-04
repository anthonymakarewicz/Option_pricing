#include "numerical_analysis/basis_function/base_basis_function.h"

namespace OptionPricer {

    BasisFunction::BasisFunction(const unsigned int &numberBasis)
    : numberBasis_(numberBasis) {
        if (numberBasis_ <= 0) throw std::invalid_argument("Number of basis functions must be positive");
    }

    BasisFunction::~BasisFunction() = default;

}
