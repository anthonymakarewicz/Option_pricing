#ifndef BASE_ASIAN_OPTION_H
#define BASE_ASIAN_OPTION_H

#include "option/path_dependent/base_path_dependent_option.h"

namespace OptionPricer {
    class AsianOption: public PathDependentOption {
    public:
        ~AsianOption() override;

    protected:
        using PathDependentOption::PathDependentOption;
    };


    class ArithmeticAsianOption final: public AsianOption {
    public:
        ~ArithmeticAsianOption() override;
        [[nodiscard]] double calc_price() const override;

    private:
        using AsianOption::AsianOption;
        friend class ArithmeticAsianOptionFactory;
    };


    class GeometricAsianOption final: public AsianOption {
    public:
        ~GeometricAsianOption() override;
        [[nodiscard]] double calc_price() const override;

    private:
        using AsianOption::AsianOption;
        friend class GeometricAsianOptionFactory;
    };
}

#endif //BASE_ASIAN_OPTION_H
