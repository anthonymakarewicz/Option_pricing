#ifndef BASE_BARRIER_OPTION_H
#define BASE_BARRIER_OPTION_H

#include "base_path_dependent_option.h"

namespace OptionPricer {

    enum class BarrierDirection { Up, Down };

    class BarrierOption : public PathDependentOption {
    public:
        ~BarrierOption() override = default;

        virtual bool isActive(const double& S) const {
            if (direction_ == BarrierDirection::Up) {
                return S >= B_;
            }
            return S <= B_; // BarrierDirection::Down
        }

    protected:
        BarrierOption(const std::string& ticker, std::unique_ptr<Payoff> payoff, const double& T, const double& B,
                      BarrierDirection direction, std::shared_ptr<IMarketData> marketData)
        : PathDependentOption(ticker, std::move(payoff), T, std::move(marketData)),
        B_(B), direction_(direction) {}

        double B_; // Barrier level
        BarrierDirection direction_;
        std::unique_ptr<Payoff> payoff_;
    };


    class KnockInBarrierOption final: public BarrierOption {
    public:
        ~KnockInBarrierOption() override = default;

        bool isActive(const double& S) const override {
            return BarrierOption::isActive(S);
        }

        double calc_price() const override {
            return 0.0;
        }

    private:
        using BarrierOption::BarrierOption;
        friend class KnockInBarrierOptionFactory;
    };


    class KnockOutBarrierOption final: public BarrierOption {
    public:
        ~KnockOutBarrierOption() override = default;

        bool isActive(const double& S) const override {
            return !BarrierOption::isActive(S);
        }

        double calc_price() const override {
            return 0.0;
        }

    private:
        using BarrierOption::BarrierOption;
        friend class KnockOutBarrierOptionFactory;
    };
};

#endif //BASE_BARRIER_OPTION_H
