#include "model/kou_model.h"
#include <random/distribution/continuous_uniform_distrib.h>
#include <random/distribution/exponential_distr.h>
#include <random/distribution/poisson_distrib.h>
#include <random/distribution/standard_normal_distribution.h>

namespace OptionPricer {

    KouModel::KouModel(const std::string &ticker,
                       std::shared_ptr<IMarketData> marketData,
                       std::shared_ptr<NumberGenerator> generator,
                       const double &lambda, const double &p,
                       const double &eta1, const double &eta2)
    : StockModel(ticker, std::move(marketData), std::move(generator)),
              lambda_(lambda), p_(p), eta1_(eta1), eta2_(eta2) {
        if (p_ < 0 || p_ > 1)
            throw std::invalid_argument("p must be between [0,1].");
        if (eta1_ < 1)
            throw std::invalid_argument("eta1 must be between larger than 1.");
        if (eta2_ < 0)
            throw std::invalid_argument("eta2 must be between larger than 0.");

    }

    KouModel::~KouModel() = default;

    double KouModel::simulatePriceAtMaturity(const double &T) const {
        return simulatePrices(T).back();
    }

    std::vector<double> KouModel::simulatePrices(const double &T) const {
        double S = stockData_->getPrice();
        const double sigma = stockData_->getSigma();
        const double r = marketData_->getR();
        const double c = stockData_->getCoupon().value_or(0.0);
        const auto steps = getSteps();
        const double dt = T / static_cast<double>(steps);

        StandardNormalDistribution snDist;
        PoissonDistribution poissonDist(lambda_ * dt);
        ContinuousUniformDistribution uniformDist;
        ExponentialDistribution exponentialDistUp(eta1_);
        ExponentialDistribution exponentialDistDown(eta2_);

        std::vector<double> prices(steps);
        for (int t = 0; t < steps; ++t) {
            // Drift Part
            const double drift = (r - c - 0.5 * sigma*sigma) * dt;

            // Diffusion part: Standard Brownian Motion
            const double z = (*generator_)(snDist);
            const double diffusion = sigma * sqrt(dt) * z;

            // Jump part: Compound Poisson process
            const int jumpCount = static_cast<int>((*generator_)(poissonDist));
            double jumpSize = 0.0;
            for (int j = 0; j < jumpCount; ++j) {
                const double U = (*generator_)(uniformDist);
                if (U < p_) {
                    const double upsideJump = (*generator_)(exponentialDistUp);
                    jumpSize += upsideJump;
                }
                const double downsideJump = -(*generator_)(exponentialDistDown);
                jumpSize += downsideJump;
            }

            // Update stock price
            S *= exp(drift + diffusion + jumpSize);
            prices[t] = S;
        }

        return prices;
    }

}
