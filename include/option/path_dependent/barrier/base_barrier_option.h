#ifndef BASE_BARRIER_OPTION_H
#define BASE_BARRIER_OPTION_H

#include "../base_path_dependent_option.h"
#include "knock_behavior.h"

namespace OptionPricer {
    class BarrierOption: public PathDependentOption {
    public:
        ~BarrierOption() override;

        double payoff(double S) const;

    protected:
        BarrierOption(const std::string& ticker, std::unique_ptr<Payoff> payoff, const double& T,
            std::shared_ptr<IMarketData> marketData, std::unique_ptr<KnockBehavior> knockBehavior);

        virtual bool isOut(double S) const = 0;

        bool isActive(double S) const;

        std::unique_ptr<KnockBehavior> knockBehavior_;
    };
}

#endif //BASE_BARRIER_OPTION_H
