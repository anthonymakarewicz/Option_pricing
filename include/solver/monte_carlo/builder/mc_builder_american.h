#ifndef MC_BUILDER_AMERICAN_H
#define MC_BUILDER_AMERICAN_H

#include "solver/monte_carlo/builder/base_mc_builder_path_dependent.h"
#include "solver/monte_carlo/mc_american.h"
//#include "solver/regression_strategy.h"
//#include "solver/basis_function_strategy.h"

namespace OptionPricer {

    class AmericanMCBuilder final : public PathDependentMCBuilder {
    public:
        using PathDependentMCBuilder::PathDependentMCBuilder;
        ~AmericanMCBuilder() override;

        AmericanMCBuilder& setOption(std::shared_ptr<Option> option) override;
        //AmericanMCPricerBuilder& setRegressionStrategy(std::shared_ptr<RegressionStrategy> regressionStrategy);
        //AmericanMCPricerBuilder& setBasisFunctionStrategy(std::shared_ptr<BasisFunctionStrategy> basisFunctionStrategy);

        std::unique_ptr<MCPricer> build() override;

    private:
        std::shared_ptr<AmericanOption> option_;
        //std::shared_ptr<RegressionStrategy> regressionStrategy_ = std::make_shared<LeastSquareRegressionStrategy>();
        //std::shared_ptr<BasisFunctionStrategy> basisFunctionStrategy_ = std::make_shared<PolynomialBasisStrategy>();
    };

}

#endif // MC_BUILDER_AMERICAN_H
