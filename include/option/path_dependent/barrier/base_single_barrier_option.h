#ifndef BASE_SINGLE_BARRIER_H
#define BASE_SINGLE_BARRIER_H

#include "base_barrier_option.h"

namespace OptionPricer {
    class SingleBarrierOption: public BarrierOption {
    public:
        ~SingleBarrierOption() override;;

    protected:
        // PROBABLY NEED TO PUT THE KnockBehavior AS WELL AS barrier INTO A PAYOFF!!
        SingleBarrierOption(const std::string& ticker, std::unique_ptr<Payoff> payoff, const double& T,
                            std::unique_ptr<KnockBehavior> knockBehavior, const double& barrier);

        double barrier_;
    };
}

#endif //BASE_SINGLE_BARRIER_H