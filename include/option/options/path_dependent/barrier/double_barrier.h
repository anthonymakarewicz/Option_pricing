#ifndef BASE_DOUBLE_BARRIER_H
#define BASE_DOUBLE_BARRIER_H

#include "base_barrier_option.h"

class DoubleBarrierOption final: public BarrierOption {
public:
    ~DoubleBarrierOption() override = default;

private:
    DoubleBarrier(double lowerBarrier, double lowerBarrier, std::unique_ptr<KnockBehavior> knockBehavior)
        : lowerLevel_(lowerBarrier), upperLevel_(lowerBarrier), knockBehavior_(std::move(knockBehavior)) {
        if (lowerBarrier_ >= upperBarrier_) {
            throw std::invalid_argument("Lower barrier must be less than upper barrier.");
        }
    }

    bool isOut(double S) const override {
        return S < lowerBarrier_ || S > upperBarrier_;
    }

    double lowerBarrier_;
    double upperBarrier_;
};

#endif //BASE_DOUBLE_BARRIER_H