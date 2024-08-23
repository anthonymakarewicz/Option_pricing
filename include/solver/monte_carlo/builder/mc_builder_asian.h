#ifndef MC_BUILDER_ASIAN_H
#define MC_BUILDER_ASIAN_H

#include "solver/monte_carlo/builder/base_mc_builder.h"
#include "solver/monte_carlo/mc_asian.h"
#include "option/path_dependent/asian_option.h"

namespace OptionPricer {

    class ArithmeticAsianMCBuilder final : public MCBuilder {
    public:
        using MCBuilder::MCBuilder;
        ~ArithmeticAsianMCBuilder() override = default;

        ArithmeticAsianMCBuilder& setOption(std::shared_ptr<Option> option) override;
        std::unique_ptr<MCPricer> build() override;

    private:
        std::shared_ptr<ArithmeticAsianOption> option_;
    };

    class GeometricAsianMCBuilder final : public MCBuilder {
    public:
        using MCBuilder::MCBuilder;
        ~GeometricAsianMCBuilder() override = default;

        GeometricAsianMCBuilder& setOption(std::shared_ptr<Option> option) override;
        std::unique_ptr<MCPricer> build() override;

    private:
        std::shared_ptr<GeometricAsianOption> option_;
    };

}

#endif // MC_BUILDER_ASIAN_H
