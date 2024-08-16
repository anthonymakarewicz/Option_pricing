#ifndef BASE_MC_PATH_DEPENDENT_H
#define BASE_MC_PATH_DEPENDENT_H

#include "solver/monte_carlo/base_mc.h"

namespace OptionPricer {

    class PathDependentMCPricer : public MCPricer {
    public:
        PathDependentMCPricer(std::shared_ptr<IMarketData> marketData,
                              std::shared_ptr<StockModel> stockModel,
                              std::shared_ptr<NumberGenerator> generator,
                              const unsigned int& steps);

    protected:
        unsigned int steps_;
    };

}

#endif //BASE_MC_PATH_DEPENDENT_H
