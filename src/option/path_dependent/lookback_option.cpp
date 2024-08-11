#include "option/path_dependent/lookback_option.h"

namespace OptionPricer {

    LookbackOption::~LookbackOption() = default;

    FloatingStrikeLookbackOption::~FloatingStrikeLookbackOption() = default;

    double FloatingStrikeLookbackOption::calc_price() const {
        return 0.0;
    }

    FixedStrikeLookbackOption::~FixedStrikeLookbackOption() = default;

    double FixedStrikeLookbackOption::calc_price() const {
        return 0.0;
    }

}
