#ifndef FACTORY_LOOKBACK_OPTION_H
#define FACTORY_LOOKBACK_OPTION_H

#include "option/factory_option.h"

namespace OptionPricer {

    class FloatingStrikeLookbackOptionFactory final: public OptionFactory {
    public:
        std::unique_ptr<Payoff> createSpecificPayoff(const ParameterObject& params, const PayoffType& type) override;
        std::shared_ptr<Option> createSpecificOption(const ParameterObject& params,
                                                     std::unique_ptr<Payoff> payoff,
                                                     const std::shared_ptr<IMarketData>& marketData) override;
        std::string getType(const PayoffType& type) const override;
    };

    class FixedStrikeLookbackOptionFactory final: public OptionFactory {
    public:
        std::unique_ptr<Payoff> createSpecificPayoff(const ParameterObject& params, const PayoffType& type) override;
        std::shared_ptr<Option> createSpecificOption(const ParameterObject& params,
                                                     std::unique_ptr<Payoff> payoff,
                                                     const std::shared_ptr<IMarketData>& marketData) override;
        std::string getType(const PayoffType& type) const override;
    };

}

#endif //FACTORY_LOOKBACK_OPTION_H
