#ifndef DOWN_SINGLE_BARRIER_OPTION_H
#define DOWN_SINGLE_BARRIER_OPTION_H

#include "base_single_barrier_option.h"

class DownSingleBarrierOption final: public SingleBarrierOption {
public:
    ~DownSingleBarrierOption() override;
    [[nodiscard]] double calc_price() const override;

private:
    DownSingleBarrierOption(const std::string& ticker, std::unique_ptr<Payoff> payoff, const double& T,
    std::unique_ptr<KnockBehavior> knockBehavior, const double& barrier);

    bool isOut(double S) const override;
};

#endif //DOWN_SINGLE_BARRIER_OPTION_H
