#ifndef MC_BUILDER_BARRIER_H
#define MC_BUILDER_BARRIER_H

#include "solver/monte_carlo/builder/base_mc_builder.h"
#include "solver/monte_carlo/mc_barrier.h"

namespace OptionPricer {

    class KnockInBarrierMCBuilder final: public MCBuilder {
    public:
        using MCBuilder::MCBuilder;
        ~KnockInBarrierMCBuilder() override = default;

        KnockInBarrierMCBuilder& setOption(std::shared_ptr<Option> option) override;
        std::unique_ptr<MCPricer> build() override;

    private:
        std::shared_ptr<KnockInBarrierOption> option_;
    };

    class KnockOutBarrierMCBuilder final: public MCBuilder {
    public:
        using MCBuilder::MCBuilder;
        ~KnockOutBarrierMCBuilder() override = default;

        KnockOutBarrierMCBuilder& setOption(std::shared_ptr<Option> option) override;
        std::unique_ptr<MCPricer> build() override;

    private:
        std::shared_ptr<KnockOutBarrierOption> option_;
    };

}

#endif // MC_BUILDER_BARRIER_H
