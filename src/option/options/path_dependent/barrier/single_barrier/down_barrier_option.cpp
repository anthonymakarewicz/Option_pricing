#ifndef DOWN_BARRIER_OPTION_CPP
#define DOWN_BARRIER_OPTION_CPP

#include "base_single_barrier_option.h"

class DownBarrierOption final : public SingleBarrier {
public:
    ~DownBarrierOption() override = default;

private:
    DownBarrierOption(const std::string& ticker, std::unique_ptr<Payoff>&& payoff, const double& T,
    std::unique_ptr<KnockBehavior> knockBehavior, const double& barrier);

    bool isOut(double S) const override {
        return S < barrier_;
    }
};

#endif //DOWN_BARRIER_OPTION_CPP
