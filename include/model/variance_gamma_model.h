#ifndef VARIANCE_GAMMA_MODEL_H
#define VARIANCE_GAMMA_MODEL_H

#include "model/base_model.h"

namespace OptionPricer {

    class VarianceGammaModel : public StockModel {
    public:
        VarianceGammaModel(const std::string& ticker,
                           std::shared_ptr<IMarketData> marketData,
                           std::shared_ptr<NumberGenerator> generator,
                           const double& sigma, const double& nu, const double& theta);

        ~VarianceGammaModel() override;

        [[nodiscard]] double simulatePriceAtMaturity(const double& T) const override;
        [[nodiscard]] std::vector<double> simulatePrices(const double& T) const override;

    private:
        double sigma_; // Volatility parameter
        double nu_;    // Variance rate of the Gamma process
        double theta_; // Drift of the Brownian motion
        double omega_; // Drift correction term
    };

}

#endif //VARIANCE_GAMMA_MODEL_H