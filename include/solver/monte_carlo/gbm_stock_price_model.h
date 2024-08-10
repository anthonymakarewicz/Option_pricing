#ifndef GBM_STOCK_PRICE_MODEL_H
#define GBM_STOCK_PRICE_MODEL_H

#include <cmath>
#include <random>
#include <solver/monte_carlo/stock_price_model.h>
#include <market_data/interface_market_data.h>

// COuld potentially make BrownianMotionModel accept a RNGenerator object so as generate the noise inside.
// It can be useful for more complex models like Variance Gamma whihc may need to genearte complicated varianbles
// Or evne jump difusion whihc will generate a set of poissonns rv that will be inside

namespace OptionPricer {
    class BrownianMotionModel : public StockPriceModel {
    public:
        BrownianMotionModel(const std::string& ticker, std::shared_ptr<IMarketData> marketData)
            : StockPriceModel(ticker, std::move(marketData)) {}

        [[nodiscard]] double simulatePriceAtMaturity(const double& T, const double& z) const override {
            const double drift = (marketData_->getR() - (0.5 * stockData_->getSigma()*stockData_->getSigma())) * T;
            const double diffusion = stockData_->getSigma() * sqrt(T) * z;
            return stockData_->getPrice() * exp(drift+diffusion);
        }

        [[nodiscard]] double simulateStepPrice(
                                               const double& dt, const double& z) const override {
            const double drift = (marketData_->getR() - (0.5 * stockData_->getSigma()*stockData_->getSigma())) * dt;
            const double diffusion = stockData_->getSigma() * sqrt(dt) * z;
            return exp(drift+diffusion);
        }
    };
}

#endif //GBM_STOCK_PRICE_MODEL_H
