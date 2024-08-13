#ifndef MC_AMERICAN_H
#define MC_AMERICAN_H

#include "solver/monte_carlo/base_mc_path_dependent.h"
#include "option/path_dependent/american_option.h"

namespace OptionPricer {

    class AmericanMCPricer final: public PathDependentMCPricer {
    public:
        AmericanMCPricer(std::shared_ptr<AmericanOption> option,
                         std::shared_ptr<IMarketData> marketData,
                         std::shared_ptr<StockPriceModel> stockModel,
                         std::shared_ptr<NumberGenerarator> generator,
                         const unsigned int& steps);
                           //std::shared_ptr<RegressionStrategy> regressionStrategy,
                           //std::shared_ptr<BasisFunctionStrategy> basisFunctionStrategy);

        double calculate_price(const unsigned long& N) const override;

    private:
        std::shared_ptr<AmericanOption> option_;
    };

}


#endif //MC_AMERICAN_H
