#ifndef UP_SINGLE_BARRIER_OPTION_H
#define UP_SINGLE_BARRIER_OPTION_H

#include "base_single_barrier_option.h"

class UpSingleBarrierOption final: public SingleBarrierOption {
public:
    ~UpSingleBarrierOption() override;
    [[nodiscard]] double calc_price() const override;

private:
    UpSingleBarrierOption(const std::string& ticker, std::unique_ptr<Payoff> payoff, const double& T,
    std::unique_ptr<KnockBehavior> knockBehavior, const double& barrier);

    bool isOut(double S) const override;
};

#endif //UP_SINGLE_BARRIER_OPTION_H