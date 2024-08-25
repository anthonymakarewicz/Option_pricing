#include "model/bates_model.h"
#include "model/discretization/explicit_euler_cir_discretization.h"
#include <random/distribution/standard_normal_distribution.h>
#include <random/distribution/poisson_distrib.h>
#include <random/distribution/normal_distrib.h>

namespace OptionPricer {

    BatesModel::BatesModel(const std::string& ticker,
                           std::shared_ptr<IMarketData> marketData,
                           std::shared_ptr<NumberGenerator> generator,
                           const double& kappa, const double& theta,
                           const double& sigma_v, const double& rho, const double& v0,
                           const double& lambda, const double& muJ, const double& sigmaJ,
                           std::shared_ptr<CIRDiscretization> varDiscretization)
        : StockModel(ticker, std::move(marketData), std::move(generator)),
          kappa_(kappa), theta_(theta), sigma_v_(sigma_v), rho_(rho), v0_(v0),
          lambda_(lambda), muJ_(muJ), sigmaJ_(sigmaJ), varDiscretization_(std::move(varDiscretization)) {
        if (v0_ <= 0.0 || kappa_ <= 0.0 || sigma_v_ <= 0.0 || sigmaJ_ <= 0.0) {
            throw std::invalid_argument("v0, kappa, sigma_v, and sigmaJ must be positive");
        }
        if (rho_ < -1.0 || rho_ > 1.0) {
            throw std::invalid_argument("rho must be between -1 and 1");
        }
        if (!varDiscretization_)
            varDiscretization_ = std::make_shared<CIRExplicitEulerDiscretization>();
    }

    BatesModel::~BatesModel() = default;

    double BatesModel::simulatePriceAtMaturity(const double& T) const {
        return simulatePrices(T).back();
    }

    std::vector<double> BatesModel::simulatePrices(const double& T) const {
        double S = stockData_->getPrice();
        double V = v0_;
        const double r = marketData_->getR();
        const double c = stockData_->getCoupon().value_or(0.0);
        const auto steps = getSteps();
        const double dt = T / static_cast<double>(steps);

        StandardNormalDistribution snd;
        PoissonDistribution poissonDist(lambda_ * dt);
        NormalDistribution jumpDist(muJ_, sigmaJ_);

        std::vector<double> prices(steps);
        for (int t = 0; t < steps; ++t) {

            // Generate correlated Brownian motions
            const double z1 = (*generator_)(snd);
            const double z2 = (*generator_)(snd);
            const double zV = z1;
            const double zS = rho_ * z1 + sqrt(1 - rho_*rho_) * z2;

            // Update stock price S(t+1) using variance v(t)
            const double VMax = std::max(V, 0.0);
            const double drift = (r - c - 0.5 * VMax) * dt;
            const double diffusion = sqrt(VMax * dt) * zS;
            S *= exp(drift + diffusion);

            // Add jumps from a compound Poisson process
            const int jump_count = static_cast<int>((*generator_)(poissonDist));
            for (int j = 0; j < jump_count; ++j) {
                const double jumpSize = (*generator_)(jumpDist);
                S *= exp(jumpSize);
            }

            prices[t] = S;

            // Update variance V(t+1) using variance V(t)
            varDiscretization_->update(V, dt, kappa_, theta_, sigma_v_, zV);
        }

        return prices;
    }

}
