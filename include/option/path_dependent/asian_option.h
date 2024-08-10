#ifndef BASE_ASIAN_OPTION_H
#define BASE_ASIAN_OPTION_H

#include "option/path_dependent/base_path_dependent_option.h"

namespace OptionPricer {
    class AsianOption: public PathDependentOption {
    public:
        ~AsianOption() override;

    protected:
        AsianOption(const std::string& ticker, std::unique_ptr<Payoff> payoff, const double& T,
            std::shared_ptr<IMarketData> marketData);
    };


    class ArithmeticAsianOption final: public AsianOption {
    public:
        ~ArithmeticAsianOption() override;
        [[nodiscard]] double calc_price() const override;

    private:
        ArithmeticAsianOption(const std::string& ticker, std::unique_ptr<Payoff> payoff, const double& T,
            std::shared_ptr<IMarketData> marketData);

        friend class ArithmeticAsianOptionFactory;
    };


    class GeometricAsianOption final: public AsianOption {
    public:
        ~GeometricAsianOption() override;
        [[nodiscard]] double calc_price() const override;

    private:
        GeometricAsianOption(const std::string& ticker, std::unique_ptr<Payoff> payoff, const double& T,
            std::shared_ptr<IMarketData> marketData);

        friend class GeometricAsianOptionFactory;
    };
}

#endif //BASE_ASIAN_OPTION_H
