#include "model/variance_gamma_model.h"

#include <random/distribution/standard_normal_distribution.h>

#include "random/distribution/gamma_distrib.h"
#include "random/distribution/normal_distrib.h"

namespace OptionPricer {

    VarianceGammaModel::VarianceGammaModel(const std::string &ticker,
                                           std::shared_ptr<IMarketData> marketData,
                                           std::shared_ptr<NumberGenerator> generator,
                                           const double &nu, const double &theta)
        : StockModel(ticker, std::move(marketData), std::move(generator)),
          nu_(nu), theta_(theta) {
        if (nu_ <= 0.0) {
            throw std::invalid_argument("nu must be positive");
        }

        // Calculate the omega correction term that makes the actualized stock price a martingale
        const double sigma = stockData_->getSigma();
        omega_ = (1.0 / nu_) * std::log(1.0 - theta_*nu_ - 0.5 * sigma*sigma * nu_);
    }

    VarianceGammaModel::~VarianceGammaModel() = default;

    double VarianceGammaModel::simulatePriceAtMaturity(const double &T) const {
        return simulatePrices(T).back();
    }

    std::vector<double> VarianceGammaModel::simulatePrices(const double &T) const {
        double S = stockData_->getPrice();
        const double sigma = stockData_->getSigma();
        const double r = marketData_->getR();
        const double c = stockData_->getCoupon().value_or(0.0);
        const auto steps = getSteps();
        const double dt = T / static_cast<double>(steps);

        StandardNormalDistribution snDist;
        GammaDistribution gammaDist(dt / nu_, nu_);

        std::vector<double> prices(steps);
        for (int t = 0; t < steps; ++t) {
            const double g = (*generator_)(gammaDist); // Gamma subordinator
            const double z = (*generator_)(snDist);  // Normal distributed increment

            const double drift = (r - c + omega_) * dt;
            const double VG = theta_ * g + sigma * std::sqrt(g) * z;

            S *= std::exp(drift + VG);
            prices[t] = S;
        }

        return prices;
    }

}
