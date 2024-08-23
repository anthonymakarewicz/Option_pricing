#ifndef MC_BUILDER_LOOKBACK_H
#define MC_BUILDER_LOOKBACK_H

#include "solver/monte_carlo/builder/base_mc_builder.h"
#include "solver/monte_carlo/mc_lookback.h"

namespace OptionPricer {

    class FloatingStrikeLookbackMCBuilder final : public MCBuilder {
    public:
        using MCBuilder::MCBuilder;
        ~FloatingStrikeLookbackMCBuilder() override;

        FloatingStrikeLookbackMCBuilder& setOption(std::shared_ptr<Option> option) override;
        std::unique_ptr<MCPricer> build() override;

    private:
        std::shared_ptr<FloatingStrikeLookbackOption> option_;
    };

    class FixedStrikeLookbackMCBuilder final : public MCBuilder {
    public:
        using MCBuilder::MCBuilder;
        ~FixedStrikeLookbackMCBuilder() override;

        FixedStrikeLookbackMCBuilder& setOption(std::shared_ptr<Option> option) override;
        std::unique_ptr<MCPricer> build() override;

    private:
        std::shared_ptr<FixedStrikeLookbackOption> option_;
    };

}

#endif // MC_BUILDER_LOOKBACK_H
