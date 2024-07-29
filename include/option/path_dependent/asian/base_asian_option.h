#ifndef BASE_ASIAN_OPTION_H
#define BASE_ASIAN_OPTION_H

#include "../base_path_dependent_option.h"

namespace OptionPricer {
    class AsianOption: public PathDependentOption {
    public:
        ~AsianOption() override;

    protected:
        AsianOption(const std::string& ticker, std::unique_ptr<Payoff> payoff, const double& T);
    };
}

#endif //BASE_ASIAN_OPTION_H
