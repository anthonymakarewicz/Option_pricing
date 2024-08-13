#ifndef BASE_MC_H
#define BASE_MC_H

#include "solver/monte_carlo/stock_price_model.h"
#include "solver/monte_carlo/generator.h"

namespace OptionPricer {

    class MCPricer {
    public:
        MCPricer(std::shared_ptr<IMarketData> marketData,
                 std::shared_ptr<StockPriceModel> stockModel,
                 std::shared_ptr<NumberGenerarator> generator);

        virtual ~MCPricer();

        [[nodiscard]] virtual double calculate_price(const unsigned long& N) const = 0;

    protected:
        std::shared_ptr<IMarketData> marketData_;
        std::shared_ptr<StockPriceModel> stockModel_;
        std::shared_ptr<NumberGenerarator> generator_;
    };

}

#endif //BASE_MC_H
