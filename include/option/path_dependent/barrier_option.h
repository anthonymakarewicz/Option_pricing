#ifndef BASE_BARRIER_OPTION_H
#define BASE_BARRIER_OPTION_H

#include "base_path_dependent_option.h"

namespace OptionPricer {

    enum class BarrierDirection {
        Up, Down
    };

    // Base Barrier
    class BarrierOption : public PathDependentOption {
    public:
        ~BarrierOption() override;

        virtual bool isActive(const double& S) const;

    protected:
        BarrierOption(const std::string& ticker, std::unique_ptr<Payoff> payoff, const double& T, const double& B,
                      BarrierDirection direction, std::shared_ptr<IMarketData> marketData);

        double B_; // Barrier level
        BarrierDirection direction_;
        std::unique_ptr<Payoff> payoff_;
    };

    // Knock-In Barrier
    class KnockInBarrierOption final: public BarrierOption {
    public:
        ~KnockInBarrierOption() override;

        bool isActive(const double& S) const override;

        double calc_price() const override;

    private:
        using BarrierOption::BarrierOption;
        friend class KnockInBarrierOptionFactory;
    };

    // Knock-Out Barrier
    class KnockOutBarrierOption final: public BarrierOption {
    public:
        ~KnockOutBarrierOption() override;

        bool isActive(const double& S) const override;

        double calc_price() const override;

    private:
        using BarrierOption::BarrierOption;
        friend class KnockOutBarrierOptionFactory;
    };

};

#endif //BASE_BARRIER_OPTION_H
