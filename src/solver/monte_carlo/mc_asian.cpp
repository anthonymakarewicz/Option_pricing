#include "solver/monte_carlo/mc_asian.h"

namespace OptionPricer {

    // Base Asian
    AsianMCPricer::AsianMCPricer(std::shared_ptr<AsianOption> option,
                                 std::shared_ptr<IMarketData> marketData,
                                 std::shared_ptr<StockModel> stockModel)
    : MCPricer(std::move(marketData),
    std::move(stockModel)), option_(std::move(option)) {}

    double AsianMCPricer::calculatePrice(const unsigned long& N) const {
        double sumPayoff = 0.0;
        const unsigned int steps = stockModel_->getSteps();
        const double discountFactor = exp(-marketData_->getR() * option_->getT());

        for (unsigned long i = 0; i < N; ++i) {
            double sumPrices = 0.0;
            std::vector<double> S = stockModel_->simulatePrices(option_->getT());

            for (int t = 0; t < steps; ++t) {
                sumPrices += computeSumPrices(S[t]);
            }

            const double averagePrice = computeAveragePrice(sumPrices, steps);
            sumPayoff += option_->payoff(averagePrice);
        }

        return (sumPayoff / static_cast<double>(N)) * discountFactor;
    }

    // Arithmetic Asian
    ArithmeticAsianMCPricer::ArithmeticAsianMCPricer(std::shared_ptr<ArithmeticAsianOption> option,
                                                     std::shared_ptr<IMarketData> marketData,
                                                     std::shared_ptr<StockModel> stockModel)
    : AsianMCPricer(std::move(option),std::move(marketData),
        std::move(stockModel)) {}

    double ArithmeticAsianMCPricer::computeSumPrices(const double &S_t) const {
        return S_t;
    }

    double ArithmeticAsianMCPricer::computeAveragePrice(const double &averagePrice, const unsigned int &steps) const {
        return averagePrice / static_cast<double>(steps);
    }

    // Geometric Asian
    GeometricAsianMCPricer::GeometricAsianMCPricer(std::shared_ptr<GeometricAsianOption> option,
                                                   std::shared_ptr<IMarketData> marketData,
                                                   std::shared_ptr<StockModel> stockModel)
    : AsianMCPricer(std::move(option),std::move(marketData),
        std::move(stockModel)) {}

    double GeometricAsianMCPricer::computeSumPrices(const double &S_t) const {
        return log(S_t);
    }

    double GeometricAsianMCPricer::computeAveragePrice(const double &averagePrice, const unsigned int &steps) const {
        return exp(averagePrice / static_cast<double>(steps));
    }

}

