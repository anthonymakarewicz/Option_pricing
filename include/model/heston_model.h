#ifndef HESTON_MODEL_H
#define HESTON_MODEL_H

#include "model/base_model.h"
#include "model/discretization/base_cir_discretization.h"

namespace OptionPricer {

    class HestonModel final : public StockModel {
    public:
        HestonModel(const std::string& ticker,
                    std::shared_ptr<IMarketData> marketData,
                    std::shared_ptr<NumberGenerator> generator,
                    const double& kappa, const double& theta, const double& sigma_v,
                    const double& rho, const double& v0,
                    std::shared_ptr<CIRDiscretization> varDiscretization = nullptr);
        ~HestonModel() override;

        [[nodiscard]] double simulatePriceAtMaturity(const double& T) const override;
        [[nodiscard]] std::vector<double> simulatePrices(const double& T) const override;

    private:
        double kappa_;  // Mean reversion rate
        double theta_;  // Long-term variance
        double sigma_v_; // Volatility of variance
        double rho_;  // Correlation between the two Brownian motions
        double v0_;  // Initial variance
        std::shared_ptr<CIRDiscretization> varDiscretization_; // Discretization scheme for the variance process
    };

}




#endif //HESTON_MODEL_H
