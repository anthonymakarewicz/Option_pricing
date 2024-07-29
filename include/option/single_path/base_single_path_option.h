#ifndef SINGLE_PATH_OPTION_H
#define SINGLE_PATH_OPTION_H

#include "option/base_option.h"

namespace OptionPricer {
    class SinglePathOption : public Option {
    public:
        ~SinglePathOption() override;

    protected:
        // Protected parameterized constructor to enforce creation through factory method
        SinglePathOption(const std::string& ticker, std::unique_ptr<Payoff> payoff, const double& T);
    };
}

#endif //SINGLE_PATH_OPTION_H
