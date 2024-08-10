#include "payoff/single_strike/base_payoff_vanilla.h"

namespace OptionPricer {
    PayoffVanilla::PayoffVanilla(const double &K) : PayoffSingleStrike(K) {}

    PayoffVanilla::~PayoffVanilla() = default;
}