#ifndef MC_BUILDER_BARRIER_H
#define MC_BUILDER_BARRIER_H

#include "solver/monte_carlo/builder/base_mc_builder_path_dependent.h"
#include "solver/monte_carlo/mc_barrier.h"

namespace OptionPricer {

    class KnockInBarrierMCBuilder final: public PathDependentMCBuilder {
    public:
        using PathDependentMCBuilder::PathDependentMCBuilder;
        ~KnockInBarrierMCBuilder() override = default;

        KnockInBarrierMCBuilder& setOption(std::shared_ptr<Option> option) override;
        std::unique_ptr<MCPricer> build() override;

    private:
        std::shared_ptr<KnockInBarrierOption> option_;
    };

    class KnockOutBarrierMCBuilder final: public PathDependentMCBuilder {
    public:
        using PathDependentMCBuilder::PathDependentMCBuilder;
        ~KnockOutBarrierMCBuilder() override = default;

        KnockOutBarrierMCBuilder& setOption(std::shared_ptr<Option> option) override;
        std::unique_ptr<MCPricer> build() override;

    private:
        std::shared_ptr<KnockOutBarrierOption> option_;
    };

}

#endif // MC_BUILDER_BARRIER_H
