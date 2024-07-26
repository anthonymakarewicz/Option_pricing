#ifndef DOUBLE_BARRIER_H
#define DOUBLE_BARRIER_H

#include "base_barrier_option.h"

class DoubleBarrierOption final: public BarrierOption {
public:
    ~DoubleBarrierOption() override;
    [[nodiscard]] double calc_price() const override;

private:
    DoubleBarrierOption(const std::string &ticker, std::unique_ptr<Payoff> &&payoff, const double &T,
                        std::unique_ptr<KnockBehavior> knockBehavior,
                        const double& lowerBarrier, const double& upperBarrier);

    bool isOut(double S) const override;

    double lowerBarrier_;
    double upperBarrier_;
};

#endif //DOUBLE_BARRIER_H