#ifndef BASE_BARRIER_OPTION_CPP
#define BASE_BARRIER_OPTION_CPP

#include "../base_path_dependent_option.h"
#include "knock_behavior.h"


class BarrierOption: public PathDependentOption {
public:
    ~BarrierOption() override = default;

    double payoff(double S) const {
        if (!isActive(S)) {
            return 0.0;
        }
        return Option::payoff(S);
    }

protected:
    BarrierOption(const std::string& ticker, std::unique_ptr<Payoff>&& payoff, const double& T,
                  std::unique_ptr<KnockBehavior> knockBehavior);

    virtual bool isOut(double S) = 0;

    bool isActive(double S) const {
        return knockBehavior_->isActive(isOut(S));
    }

    std::unique_ptr<KnockBehavior> knockBehavior_;
    friend class PathDependentOptionFactory;
};

#endif //BASE_BARRIER_OPTION_CPP
