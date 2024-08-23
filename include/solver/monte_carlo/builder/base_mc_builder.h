#ifndef BASE_MC_BUILDER_H
#define BASE_MC_BUILDER_H

#include "solver/monte_carlo/base_mc.h"
#include "option/base_option.h"
#include "model/base_model.h"
#include <random/number_generator/pseudo_random_generator.h>
#include "model/gbm_model.h"

namespace OptionPricer {

    class MCBuilder {
    public:
        MCBuilder();
        virtual ~MCBuilder();

        MCBuilder& setMarketData(std::shared_ptr<IMarketData> marketData);
        MCBuilder& setStockPriceModel(std::shared_ptr<StockModel> stockModel);

        virtual MCBuilder& setOption(std::shared_ptr<Option> option) = 0;
        virtual std::unique_ptr<MCPricer> build() = 0;

    protected:
        std::shared_ptr<IMarketData> marketData_;
        std::shared_ptr<StockModel> stockModel_; // Requires specific option to be provided default values
    };

}

#endif //BASE_MC_BUILDER_H
