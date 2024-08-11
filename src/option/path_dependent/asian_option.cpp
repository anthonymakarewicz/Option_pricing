#include "option/path_dependent/asian_option.h"

namespace OptionPricer {
    AsianOption::~AsianOption() = default;

    ArithmeticAsianOption::~ArithmeticAsianOption() = default;

    double ArithmeticAsianOption::calc_price() const {
        return 0.0;
    }

    GeometricAsianOption::~GeometricAsianOption() = default;

    double GeometricAsianOption::calc_price() const {
        return 0.0;
    }
}
