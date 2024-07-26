#ifndef BASE_SINGLE_BARRIER_CPP
#define BASE_SINGLE_BARRIER_CPP

#include "../base_barrier_option.h"

class SingleBarrierOption: public BarrierOption {
public:
    ~SingleBarrierOption() override = default;

protected:
    SingleBarrierOption(const std::string& ticker, std::unique_ptr<Payoff>&& payoff, const double& T,
    std::unique_ptr<KnockBehavior> knockBehavior, const double& barrier);

    double barrier_;
    friend class PathDependentOptionFactory;
};

#endif //BASE_SINGLE_BARRIER_CPP