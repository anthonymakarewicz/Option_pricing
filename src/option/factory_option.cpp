#include "option/factory_option.h"

namespace OptionPricer {
    std::string OptionFactory::invalidParams(const std::string &option_type) const {
        return "Invalid parameters for " + option_type + "\n"
          "Expected parameters:\n"
          "  - ticker (string) for ticker symbol\n"
          "  - T (double) for maturity\n"
          "  - K (double) for strike\n";
    }
}
