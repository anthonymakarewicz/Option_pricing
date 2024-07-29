#include "option/path_dependent/barrier/knock_behavior.h"

namespace OptionPricer {
    KnockBehavior::~KnockBehavior() = default;

    KnockIn::~KnockIn() = default;

    bool KnockIn::isActive(bool barrierBreached) const {
        return barrierBreached;
    }

    KnockOut::~KnockOut() = default;

    bool KnockOut::isActive(bool barrierBreached) const {
        return !barrierBreached;
    }
}