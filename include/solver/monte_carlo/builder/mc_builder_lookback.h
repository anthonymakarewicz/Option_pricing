#ifndef MC_BUILDER_LOOKBACK_H
#define MC_BUILDER_LOOKBACK_H

#include "solver/monte_carlo/builder/base_mc_builder_path_dependent.h"
#include "solver/monte_carlo/mc_lookback.h"

namespace OptionPricer {

    class FloatingStrikeLookbackMCBuilder final : public PathDependentMCBuilder {
    public:
        using PathDependentMCBuilder::PathDependentMCBuilder;
        ~FloatingStrikeLookbackMCBuilder() override;

        FloatingStrikeLookbackMCBuilder& setOption(std::shared_ptr<Option> option) override;
        std::unique_ptr<MCPricer> build() override;

    private:
        std::shared_ptr<FloatingStrikeLookbackOption> option_;
    };

    class FixedStrikeLookbackMCBuilder final : public PathDependentMCBuilder {
    public:
        using PathDependentMCBuilder::PathDependentMCBuilder;
        ~FixedStrikeLookbackMCBuilder() override;

        FixedStrikeLookbackMCBuilder& setOption(std::shared_ptr<Option> option) override;
        std::unique_ptr<MCPricer> build() override;

    private:
        std::shared_ptr<FixedStrikeLookbackOption> option_;
    };

}

#endif // MC_BUILDER_LOOKBACK_H
