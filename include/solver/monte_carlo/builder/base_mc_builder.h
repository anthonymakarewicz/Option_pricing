#ifndef BASE_MC_BUILDER_H
#define BASE_MC_BUILDER_H

#include "solver/monte_carlo/base_mc.h"
#include "model/base_model.h"
#include "model/gbm_model.h"
#include "option/base_option.h"

namespace OptionPricer {

    class MCBuilder {
    public:
        MCBuilder();
        virtual ~MCBuilder();

        MCBuilder& setMarketData(std::shared_ptr<IMarketData> marketData);
        MCBuilder& setStockPriceModel(std::shared_ptr<StockModel> stockModel);
        MCBuilder& setNumberGenerator(std::shared_ptr<NumberGenerator> generator);

        virtual MCBuilder& setOption(std::shared_ptr<Option> option) = 0;
        virtual std::unique_ptr<MCPricer> build() = 0;

    protected:
        std::shared_ptr<IMarketData> marketData_;
        std::shared_ptr<StockModel> stockModel_; // Requires specific option to be provided default values
        std::shared_ptr<NumberGenerator> generator_;
    };

}

#endif //BASE_MC_BUILDER_H
