#ifndef MC_BUILDER_AMERICAN_H
#define MC_BUILDER_AMERICAN_H

#include "solver/monte_carlo/builder/base_mc_builder.h"
#include "solver/monte_carlo/mc_american.h"
#include "numerical_analysis/regression/least_squares.h"
#include "numerical_analysis/basis_function/monomial.h"

namespace OptionPricer {

    class AmericanMCBuilder final : public MCBuilder {
    public:
        AmericanMCBuilder();
        ~AmericanMCBuilder() override;

        AmericanMCBuilder& setOption(std::shared_ptr<Option> option) override;
        AmericanMCBuilder& setRegressionStrategy(std::shared_ptr<Regression> regressionStrategy);
        AmericanMCBuilder& setBasisFunctionStrategy(std::shared_ptr<BasisFunction> basisFunctionStrategy);

        std::unique_ptr<MCPricer> build() override;

    private:
        std::shared_ptr<AmericanOption> option_;
        std::shared_ptr<Regression> regressionStrategy_;
        std::shared_ptr<BasisFunction> basisFunctionStrategy_;
    };

}

#endif // MC_BUILDER_AMERICAN_H
