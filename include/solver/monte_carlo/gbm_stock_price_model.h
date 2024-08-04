#ifndef GBM_STOCK_PRICE_MODEL_H
#define GBM_STOCK_PRICE_MODEL_H

#include <cmath>
#include <random>
#include <solver/monte_carlo/stock_price_model.h>
#include <market_data/interface_market_data.h>



namespace OptionPricer {
    class BrownianMotionModel : public StockPriceModel {
    public:
        BrownianMotionModel(const std::string& ticker, std::shared_ptr<IMarketData> marketData, const int seed);

        [[nodiscard]] double simulate_price(const double& maturity) const override {
            /*
            auto stockData = marketData_->getStockData(ticker_);

            std::normal_distribution<double> distribution(0.0, 1.0);
            static std::default_random_engine generator(3);

            double St = stockData->getPrice() * exp((r_ - 0.5 * sigma_ * sigma_) * dt + sigma_ * sqrt(dt) * distribution(generator));
            return St;

            */
            return 0.0;
        }
    protected:
        std::normal_distribution<double> distribution_;
    };
}



#endif //GBM_STOCK_PRICE_MODEL_H
