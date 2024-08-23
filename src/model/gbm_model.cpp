#include "model/gbm_model.h"

#include <random/distribution/standard_normal_distribution.h>

namespace OptionPricer {

    GeometricBrownianMotionModel::~GeometricBrownianMotionModel() = default;

    double GeometricBrownianMotionModel::simulatePriceAtMaturity(const double &T) const {
        return simulatePrices(T).back();
    }

    std::vector<double> GeometricBrownianMotionModel::simulatePrices(const double& T) const {
        double S = stockData_->getPrice();
        const double sigma = stockData_->getSigma();
        const double r = marketData_->getR();
        const double c = stockData_->getCoupon().value_or(0.0);
        const auto steps = getSteps();
        const double dt = T / static_cast<double>(steps);
        StandardNormalDistribution snd;

        std::vector<double> prices(steps);
        for (int t = 0; t < steps; ++t) {
            const double z = (*generator_)(snd);
            const double drift = (r - c - (0.5 * sigma*sigma)) * dt;
            const double diffusion = sigma * sqrt(dt) * z;

            S *= exp(drift + diffusion);
            prices[t] = S;
        }

        return prices;
    }

    double GeometricBrownianMotionModel::simulatePriceBackward(const double& S_next,
                                                               const double& t_j,
                                                               const double& t_jp1) const {
        const double sigma = stockData_->getSigma();
        const double S = stockData_->getPrice();
        const double X_next = log(S_next / S);

        StandardNormalDistribution snd;
        const double z = (*generator_)(snd);

        // Use the Brownian Bridge interpolation formula
        const double X_curr = (t_j/t_jp1) * X_next + sqrt(t_j * (t_jp1-t_j)/t_jp1) * sigma * z;

        return S * exp(X_curr);
    }

}