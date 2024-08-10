#ifndef BASE_PATH_DEPENDENT_OPTION_H
#define BASE_PATH_DEPENDENT_OPTION_H

#include "../base_option.h"

namespace OptionPricer {
    class PathDependentOption : public Option {
    public:
        ~PathDependentOption() override;

    protected:
        // Protected parameterized constructor to enforce creation through factory method
        PathDependentOption(const std::string& ticker, std::unique_ptr<Payoff> payoff, const double& T,
            std::shared_ptr<IMarketData> marketData);
    };
}

#endif //BASE_PATH_DEPENDENT_OPTION_H
