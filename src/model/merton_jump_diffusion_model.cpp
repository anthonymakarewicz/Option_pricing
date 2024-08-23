#include "model/merton_jump_diffusion_model.h"

#include <iostream>
#include <random/distribution/normal_distrib.h>
#include <random/distribution/poisson_distrib.h>
#include <random/distribution/standard_normal_distribution.h>

namespace OptionPricer {

    MertonJumpDiffusionModel::MertonJumpDiffusionModel(const std::string &ticker,
                                                       std::shared_ptr<IMarketData> marketData,
                                                       std::shared_ptr<NumberGenerator> generator,
                                                       const double &lambda, const double &muJ, const double &sigmaJ)
        : StockModel(ticker, std::move(marketData), std::move(generator)),
        lambda_(lambda), muJ_(muJ), sigmaJ_(sigmaJ) {
        if (sigmaJ_ <= 0)
            throw std::invalid_argument("sigmaJ must be positive");
    }

    MertonJumpDiffusionModel::~MertonJumpDiffusionModel() = default;

    double MertonJumpDiffusionModel::simulatePriceAtMaturity(const double &T) const {
        return simulatePrices(T).back();
    }

    std::vector<double> MertonJumpDiffusionModel::simulatePrices(const double &T) const {
        double S = stockData_->getPrice();
        const double sigma = stockData_->getSigma();
        const double r = marketData_->getR();
        const double c = stockData_->getCoupon().value_or(0.0);
        const auto steps = getSteps();
        const double dt = T / static_cast<double>(steps);

        StandardNormalDistribution snDist;
        PoissonDistribution poissonDist(lambda_ * dt);
        NormalDistribution jumpDist(muJ_, sigmaJ_);

        std::vector<double> prices(steps);
        for (int t = 0; t < steps; ++t) {
            // Drift Part
            const double drift = (r - c - 0.5 * sigma*sigma) * dt;

            // Diffusion part: Standard Brownian Motion
            const double z = (*generator_)(snDist);
            const double diffusion = sigma * sqrt(dt) * z;

            // Jump part: Compound Poisson process
            const int jump_count = static_cast<int>((*generator_)(poissonDist)); // Number of jumps in this step
            double jumpSize = 0.0;
            for (int j = 0; j < jump_count; ++j) {
                jumpSize += (*generator_)(jumpDist); // Add all jump sizes to the stock price
            }

            // Update stock price
            S *= exp(drift + diffusion + jumpSize);
            prices[t] = S;
        }

        return prices;
    }

}
