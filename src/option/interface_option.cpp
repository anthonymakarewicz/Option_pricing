#include "option/interface_option.h"

namespace OptionPricer {
    IOption::IOption(const std::string &id) : MarketDataObserver(id) {}

    IOption::~IOption() = default;
}