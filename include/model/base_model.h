#ifndef STOCK_PRICE_MODEL_H
#define STOCK_PRICE_MODEL_H

#include <string>
#include <random/number_generator/base_generator.h>
#include "market_data/interface_market_data.h"

namespace OptionPricer {

    class StockModel {
    public:
        StockModel(const std::string& ticker,
                   std::shared_ptr<IMarketData> marketData,
                   std::shared_ptr<NumberGenerator> generator);

        virtual ~StockModel();
        unsigned int getSteps() const;
        [[nodiscard]] std::shared_ptr<NumberGenerator> getGenerator() const;

        [[nodiscard]] virtual double simulatePriceAtMaturity(const double& T) const = 0;
        [[nodiscard]] virtual std::vector<double> simulatePrices(const double& T) const = 0;
        [[nodiscard]] virtual double simulatePriceBackward(const double& S_next,
                                                           const double& t_j,
                                                           const double& t_jp1) const;
    protected:
        std::string ticker_;
        std::shared_ptr<IMarketData> marketData_;
        std::shared_ptr<const StockData> stockData_; // Cache StockData for consultation
        std::shared_ptr<NumberGenerator> generator_;
    };

}

#endif //STOCK_PRICE_MODEL_H
