#ifndef BATES_MODEL_H
#define BATES_MODEL_H

#include "model/base_model.h"
#include "model/discretization/base_cir_discretization.h"

namespace OptionPricer {

    class BatesModel final: public StockModel {
    public:
        BatesModel(const std::string& ticker,
                   std::shared_ptr<IMarketData> marketData,
                   std::shared_ptr<NumberGenerator> generator,
                   const double& kappa, const double& theta,
                   const double& sigma_v, const double& rho, const double& v0,
                   const double& lambda, const double& muJ, const double& sigmaJ,
                   std::shared_ptr<CIRDiscretization> varDiscretization = nullptr);

        ~BatesModel() override;

        [[nodiscard]] double simulatePriceAtMaturity(const double& T) const override;
        [[nodiscard]] std::vector<double> simulatePrices(const double& T) const override;

    private:
        double kappa_, theta_, sigma_v_, rho_, v0_; // Heston parameters
        double lambda_, muJ_, sigmaJ_; //          // Merton jump diffusion parameters
        std::shared_ptr<CIRDiscretization> varDiscretization_;
    };

}

#endif // BATES_MODEL_H
