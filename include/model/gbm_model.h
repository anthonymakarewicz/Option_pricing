#ifndef GBM_STOCK_PRICE_MODEL_H
#define GBM_STOCK_PRICE_MODEL_H

#include <cmath>
#include <random>
#include <model/base_model.h>
#include <market_data/interface_market_data.h>

namespace OptionPricer {

    class GeometricBrownianMotionModel : public StockModel {
    public:
        GeometricBrownianMotionModel(const std::string& ticker, std::shared_ptr<IMarketData> marketData);

        [[nodiscard]] double simulatePriceAtMaturity(const double& T, const double& z) const override;
        [[nodiscard]] double simulateStepPrice(const double& dt, const double& z) const override;
    };

}

#endif //GBM_STOCK_PRICE_MODEL_H
