#ifndef MC_AMERICAN_H
#define MC_AMERICAN_H

#include "solver/monte_carlo/base_mc_path_dependent.h"
#include "option/path_dependent/american_option.h"
#include "solver/monte_carlo/regression/base_regression_strategy.h"
#include "solver/monte_carlo/basis_function/base_basis_function_strategy.h"

namespace OptionPricer {

    class AmericanMCPricer final: public PathDependentMCPricer {
    public:
        AmericanMCPricer(std::shared_ptr<AmericanOption> option,
                         std::shared_ptr<IMarketData> marketData,
                         std::shared_ptr<StockModel> stockModel,
                         std::shared_ptr<NumberGenerator> generator,
                         std::shared_ptr<BasisFunctionStrategy> basisFunctionStrategy,
                         std::shared_ptr<RegressionStrategy> regressionStrategy,
                         const unsigned int& steps);

        double calculate_price(const unsigned long& N) const override;
        double standardPrice(const unsigned long& N, const double &dt, const double &discountFactor) const ;
        double brownianBridgePrice(const unsigned long& N, const double &dt, const double &discountFactor) const ;

    private:
        std::shared_ptr<BasisFunctionStrategy> basisFunctionStrategy_;
        std::shared_ptr<RegressionStrategy> regressionStrategy_;
        std::shared_ptr<AmericanOption> option_;
    };

}

#endif //MC_AMERICAN_H
