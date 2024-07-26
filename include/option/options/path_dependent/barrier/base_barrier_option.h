#ifndef BASE_BARRIER_OPTION_H
#define BASE_BARRIER_OPTION_H

#include "../base_path_dependent_option.h"
#include "knock_behavior.h"

class BarrierOption: public PathDependentOption {
public:
    ~BarrierOption() override;

    double payoff(double S) const;

protected:
    BarrierOption(const std::string& ticker, std::unique_ptr<Payoff>&& payoff, const double& T,
                  std::unique_ptr<KnockBehavior> knockBehavior);

    virtual bool isOut(double S) const = 0;

    bool isActive(double S) const {
        return knockBehavior_->isActive(isOut(S));
    }

    std::unique_ptr<KnockBehavior> knockBehavior_;
};

#endif //BASE_BARRIER_OPTION_H
