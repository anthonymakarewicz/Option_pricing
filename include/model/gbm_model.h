#ifndef GBM_STOCK_PRICE_MODEL_H
#define GBM_STOCK_PRICE_MODEL_H

#include <cmath>
#include <random>
#include "model/base_model.h"

namespace OptionPricer {

    class GeometricBrownianMotionModel final: public StockModel {
    public:
        using StockModel::StockModel;
        ~GeometricBrownianMotionModel() override;

        [[nodiscard]] double simulatePriceAtMaturity(const double& T) const override;
        [[nodiscard]] std::vector<double> simulatePrices(const double& T) const override;
        [[nodiscard]] double simulatePriceBackward(const double &S_next,
                                                   const double &t_j,
                                                   const double &t_jp1) const override;
    };

}

#endif //GBM_STOCK_PRICE_MODEL_H
