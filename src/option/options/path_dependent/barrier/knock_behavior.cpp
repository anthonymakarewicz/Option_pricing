#include "option/options/path_dependent/barrier/knock_behavior.h"

KnockBehavior::~KnockBehavior() = default;

KnockIn::~KnockIn() = default;

bool KnockIn::isActive(bool barrierBreached) const {
    return barrierBreached;
}

KnockOut::~KnockOut() = default;

bool KnockOut::isActive(bool barrierBreached) const {
    return !barrierBreached;
}