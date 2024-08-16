#include "solver/monte_carlo/mc_asian.h"

namespace OptionPricer {

    // Base Asian
    AsianMCPricer::AsianMCPricer(std::shared_ptr<AsianOption> option,
                                 std::shared_ptr<IMarketData> marketData,
                                 std::shared_ptr<StockModel> stockModel,
                                 std::shared_ptr<NumberGenerator> generator,
                                 const unsigned int& steps)
    : PathDependentMCPricer(std::move(marketData),
    std::move(stockModel), std::move(generator), steps), option_(std::move(option)) {}

    double AsianMCPricer::calculatePrice(const unsigned long& N) const {
        double sumPayoff = 0.0;
        const double dt = option_->getT() / static_cast<double>(steps_);

        for (unsigned long i = 0; i < N; ++i) {
            double S_t = marketData_->getStockData(option_->getID())->getPrice();
            double sumPrices = 0.0;

            for (unsigned int step = 0; step < steps_; ++step) {
                double z = generator_->generate(step);
                S_t *= stockModel_->simulateStepPrice(dt, z);
                sumPrices += computeSumPrices(S_t);
            }

            const double averagePrice = computeAveragePrice(sumPrices);
            sumPayoff += option_->payoff(averagePrice);
        }

        return (sumPayoff / static_cast<double>(N)) * exp(-marketData_->getR() * option_->getT());
    }

    // Arithmetic Asian
    ArithmeticAsianMCPricer::ArithmeticAsianMCPricer(std::shared_ptr<ArithmeticAsianOption> option,
                                                     std::shared_ptr<IMarketData> marketData,
                                                     std::shared_ptr<StockModel> stockModel,
                                                     std::shared_ptr<NumberGenerator> generator,
                                                     const unsigned int &steps)
    : AsianMCPricer(std::move(option),std::move(marketData),
        std::move(stockModel), std::move(generator), steps) {}

    double ArithmeticAsianMCPricer::computeSumPrices(const double &S_t) const {
        return S_t;
    }

    double ArithmeticAsianMCPricer::computeAveragePrice(const double &averagePrice) const {
        return averagePrice / static_cast<double>(steps_);
    }

    // Geometric Asian
    GeometricAsianMCPricer::GeometricAsianMCPricer(std::shared_ptr<GeometricAsianOption> option,
                                                   std::shared_ptr<IMarketData> marketData,
                                                   std::shared_ptr<StockModel> stockModel,
                                                   std::shared_ptr<NumberGenerator> generator,
                                                   const unsigned int &steps)
    : AsianMCPricer(std::move(option),std::move(marketData),
        std::move(stockModel), std::move(generator), steps) {}

    double GeometricAsianMCPricer::computeSumPrices(const double &S_t) const {
        return log(S_t);
    }

    double GeometricAsianMCPricer::computeAveragePrice(const double &averagePrice) const {
        return exp(averagePrice / static_cast<double>(steps_));
    }

}

