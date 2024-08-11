#ifndef LOOKBACK_OPTION_H
#define LOOKBACK_OPTION_H

#include "option/path_dependent/base_path_dependent_option.h"

namespace OptionPricer {

    // Base class for Lookback options
    class LookbackOption: public PathDependentOption {
    public:
        ~LookbackOption() override;

    protected:
        using PathDependentOption::PathDependentOption;
    };

    class FloatingStrikeLookbackOption final: public LookbackOption {
    public:
        ~FloatingStrikeLookbackOption() override;
        [[nodiscard]] double calc_price() const override;

    private:
        using LookbackOption::LookbackOption;
        friend class FloatingStrikeLookbackOptionFactory;
    };

    class FixedStrikeLookbackOption final: public LookbackOption {
    public:
        ~FixedStrikeLookbackOption() override;
        [[nodiscard]] double calc_price() const override;

    private:
        using LookbackOption::LookbackOption;
        friend class FixedStrikeLookbackOptionFactory;
    };

}

#endif //LOOKBACK_OPTION_H
