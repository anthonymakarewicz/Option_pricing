#include "option/path_dependent/asian_option.h"

namespace OptionPricer {

    // Base Asian
    AsianOption::~AsianOption() = default;

    // Arithmetic Asian
    ArithmeticAsianOption::~ArithmeticAsianOption() = default;

    double ArithmeticAsianOption::calc_price() const {
        return 0.0;
    }

    // Geometric Asian
    GeometricAsianOption::~GeometricAsianOption() = default;

    double GeometricAsianOption::calc_price() const {
        return 0.0;
    }

}
