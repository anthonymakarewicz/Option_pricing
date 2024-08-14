#include "model/gbm_model.h"

namespace OptionPricer {

    GeometricBrownianMotionModel::GeometricBrownianMotionModel(const std::string &ticker, std::shared_ptr<IMarketData> marketData)
    : StockModel(ticker, std::move(marketData)) {}

    // NEED TO ADD COUPON
    double GeometricBrownianMotionModel::simulatePriceAtMaturity(const double &T, const double &z) const {
        const double drift = (marketData_->getR() - (0.5 * stockData_->getSigma()*stockData_->getSigma())) * T;
        const double diffusion = stockData_->getSigma() * sqrt(T) * z;
        return stockData_->getPrice() * exp(drift+diffusion);
    }

    double GeometricBrownianMotionModel::simulateStepPrice(const double &dt, const double &z) const  {
        const double drift = (marketData_->getR() - (0.5 * stockData_->getSigma()*stockData_->getSigma())) * dt;
        const double diffusion = stockData_->getSigma() * sqrt(dt) * z;
        return exp(drift+diffusion);
    }

}
