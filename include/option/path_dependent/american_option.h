#ifndef AMERICAN_OPTION_H
#define AMERICAN_OPTION_H

#include "base_path_dependent_option.h"

namespace OptionPricer {

    class AmericanOption final: public PathDependentOption {
    public:
        ~AmericanOption() override;
        [[nodiscard]] double calc_price() const override;

    private:
        AmericanOption(const std::string& ticker, std::unique_ptr<Payoff> payoff, const double& T,
            std::shared_ptr<IMarketData> marketData);
        friend class AmericanOptionFactory;
    };

}

#endif //AMERICAN_OPTION_H