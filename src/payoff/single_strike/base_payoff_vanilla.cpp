#include "payoff/single_strike/base_payoff_vanilla.h"

PayoffVanilla::PayoffVanilla(const double &K) : PayoffSingleStrike(K) {}

PayoffVanilla::~PayoffVanilla() = default;