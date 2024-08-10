#include "option/path_dependent/asian_option.h"

namespace OptionPricer {
    AsianOption::~AsianOption() = default;

    AsianOption::AsianOption(const std::string &ticker, std::unique_ptr<Payoff> payoff, const double &T,
        std::shared_ptr<IMarketData> marketData)
    : PathDependentOption(ticker, std::move(payoff), T, std::move(marketData)) {}


    ArithmeticAsianOption::~ArithmeticAsianOption() = default;

    double ArithmeticAsianOption::calc_price() const {
        return 0.0;
    }

    ArithmeticAsianOption::ArithmeticAsianOption(const std::string &ticker,
                                                 std::unique_ptr<Payoff> payoff,
                                                 const double &T,
                                                 std::shared_ptr<IMarketData> marketData)
    : AsianOption(ticker, std::move(payoff), T, std::move(marketData)) {}


    GeometricAsianOption::~GeometricAsianOption() = default;

    double GeometricAsianOption::calc_price() const {
        return 0.0;
    }

    GeometricAsianOption::GeometricAsianOption(const std::string &ticker,
                                               std::unique_ptr<Payoff> payoff,
                                               const double &T,
                                               std::shared_ptr<IMarketData> marketData)
    : AsianOption(ticker, std::move(payoff), T, std::move(marketData)) {}
}
