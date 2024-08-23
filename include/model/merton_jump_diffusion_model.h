#ifndef MERTON_JUMP_DIFFUSION_MODEL_H
#define MERTON_JUMP_DIFFUSION_MODEL_H

#include "model/base_model.h"

namespace OptionPricer {

    class MertonJumpDiffusionModel final : public StockModel {
    public:
        MertonJumpDiffusionModel(const std::string& ticker,
                                 std::shared_ptr<IMarketData> marketData,
                                 std::shared_ptr<NumberGenerator> generator,
                                 const double& lambda, const double& muJ, const double& sigmaJ);

        ~MertonJumpDiffusionModel() override;

        double simulatePriceAtMaturity(const double& T) const override;
        std::vector<double> simulatePrices(const double& T) const override;

    private:
        double lambda_;  // intensity of the Poisson process (mean number of jumps per unit time)
        double muJ_;     // mean of the jump size distribution
        double sigmaJ_;  // standard deviation of the jump size distribution
    };

}

#endif // MERTON_JUMP_DIFFUSION_MODEL_H