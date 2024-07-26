#ifndef UP_BARRIER_OPTION_CPP
#define UP_BARRIER_OPTION_CPP

#include "base_single_barrier_option.h"

class UpBarrierOption final : public SingleBarrier {
public:
    ~UpBarrierOption() override = default;

private:
    UpBarrierOption(const std::string& ticker, std::unique_ptr<Payoff>&& payoff, const double& T,
    std::unique_ptr<KnockBehavior> knockBehavior, const double& barrier);

    bool isOut(double S) const override {
        return S > barrier_;
    }
};

#endif //UP_BARRIER_OPTION_CPP
