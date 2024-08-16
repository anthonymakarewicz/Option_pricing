#ifndef BASE_MC_H
#define BASE_MC_H

#include <iostream>
#include "model/base_model.h"
#include "random/number_generator/base_generator.h"

namespace OptionPricer {

    class MCPricer {
    public:
        MCPricer(std::shared_ptr<IMarketData> marketData,
                 std::shared_ptr<StockModel> stockModel,
                 std::shared_ptr<NumberGenerator> generator);

        virtual ~MCPricer();

        [[nodiscard]] virtual double calculatePrice(const unsigned long& N) const = 0;

    protected:
        std::shared_ptr<IMarketData> marketData_;
        std::shared_ptr<StockModel> stockModel_;
        std::shared_ptr<NumberGenerator> generator_;
    };

}

#endif //BASE_MC_H
