#include "option/path_dependent/lookback_option.h"

namespace OptionPricer {

    // Base Lookback
    LookbackOption::~LookbackOption() = default;

    // Floating Strike Lookback
    FloatingStrikeLookbackOption::~FloatingStrikeLookbackOption() = default;

    double FloatingStrikeLookbackOption::calc_price() const {
        return 0.0;
    }

    // Fixed Strike Lookback
    FixedStrikeLookbackOption::~FixedStrikeLookbackOption() = default;

    double FixedStrikeLookbackOption::calc_price() const {
        return 0.0;
    }

}
