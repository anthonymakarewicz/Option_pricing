#include "model/heston_model.h"
#include "model/discretization/explicit_euler_cir_discretization.h"
#include "random/distribution/standard_normal_distribution.h"
#include <iostream>

namespace OptionPricer {
    HestonModel::HestonModel(const std::string& ticker,
                             std::shared_ptr<IMarketData> marketData,
                             std::shared_ptr<NumberGenerator> generator,
                             const double& kappa, const double& theta,
                             const double& sigma_v, const double& rho, const double& v0,
                             std::shared_ptr<CIRDiscretization> varDiscretization)
        : StockModel(ticker, std::move(marketData), std::move(generator)),
          kappa_(kappa), theta_(theta), sigma_v_(sigma_v), rho_(rho), v0_(v0),
          varDiscretization_(std::move(varDiscretization))  {
        if (rho_ < -1.0 || rho_ > 1.0) {
            throw std::logic_error("Correlation rho must be between [-1,1]");
        }
        if (v0_ < 0.0 || sigma_v < 0.0) {
            throw std::logic_error("Initial volatility v0 and vol of vol sigma_v must be non-negative");
        }
    /*
        if (2*kappa_*theta_ <= sigma_v_*sigma_v_) {
            throw std::logic_error("Feller's condition not satisfied.\n"
                                    "Please try again by ensuring 2*kappa*theta > sigma_v*sigma_v");
        }
        */

        // Apply default discretization if nullptr is passed
        if (!varDiscretization) {
            varDiscretization_ = std::make_shared<CIRExplicitEulerDiscretization>();
        }
    }

    HestonModel::~HestonModel() = default;

    double HestonModel::simulatePriceAtMaturity(const double& T) const {
        return simulatePrices(T).back();
    }

    std::vector<double> HestonModel::simulatePrices(const double& T) const {
        double S = stockData_->getPrice();
        double V = v0_;
        const double r = marketData_->getR();
        const double c = stockData_->getCoupon().value_or(0.0);
        const auto steps = getSteps();
        const double dt = T / static_cast<double>(steps);
        StandardNormalDistribution snd;

        std::vector<double> prices(steps);
        for (int t = 0; t < steps; ++t) {

            // Generate correlated Brownian motions
            const double z1 = (*generator_)(snd);
            const double z2 = (*generator_)(snd);
            const double zV = z1;
            const double zS = rho_ * z1 + sqrt(1 - rho_*rho_) * z2;

            // Update stock price S(t) using V(t-1)
            const double VMax = std::max(V, 0.0);
            const double drift = (r - c - 0.5 * VMax) * dt;
            const double diffusion = sqrt(VMax * dt) * zS;
            S *= exp(drift + diffusion);

            // Apply discretization scheme to the variance process (CIR process)
            varDiscretization_->update(V, dt, kappa_, theta_, sigma_v_, zV);

            prices[t] = S;
        }

        return prices;
    }
}
