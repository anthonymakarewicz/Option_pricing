#include "payoff/single_strike/base_payoff_digital.h"

namespace OptionPricer {
    PayoffDigital::PayoffDigital(const double &K) : PayoffSingleStrike(K) {}

    PayoffDigital::~PayoffDigital() = default;
}
