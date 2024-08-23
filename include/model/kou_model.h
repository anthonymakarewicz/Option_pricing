#ifndef KOU_MODEL_H
#define KOU_MODEL_H

#include "model/base_model.h"

namespace OptionPricer {

    class KouModel final: public StockModel {
    public:
        /* This class implements the Kou model which is an extension of the Merton Jump Diffusion model
         * which introduce asymmetry of jumps for modeling the skewness and kurtosis of stock returns.
         */
        KouModel(const std::string& ticker,
                 std::shared_ptr<IMarketData> marketData,
                 std::shared_ptr<NumberGenerator> generator,
                 const double& lambda, const double& p,
                 const double& eta1, const double& eta2);

        ~KouModel() override;

        double simulatePriceAtMaturity(const double& T) const override;
        std::vector<double> simulatePrices(const double& T) const override;

    private:
        double lambda_;  // Jump intensity
        double p_;       // Probability of upward jump
        double eta1_;    // Rate of upward jumps
        double eta2_;    // Rate of downward jumps
    };

}

#endif //KOU_MODEL_H
