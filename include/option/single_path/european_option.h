#ifndef EUROPEAN_OPTION_H
#define EUROPEAN_OPTION_H

#include "base_single_path_option.h"

namespace OptionPricer {
    class EuropeanOption final: public SinglePathOption {
    public:
        ~EuropeanOption() override;
        [[nodiscard]] double calc_price() const override;

        EuropeanOption(const std::string& ticker, std::unique_ptr<Payoff> payoff, const double& T,
                       std::shared_ptr<IMarketData> marketData);

    private:
    };
}

#endif //EUROPEAN_OPTION_H
