#ifndef MC_BUILDER_SINGLE_PATH_H
#define MC_BUILDER_SINGLE_PATH_H

#include "solver/monte_carlo/builder/base_mc_builder.h"
#include "solver/monte_carlo/mc_single_path.h"
#include "option/single_path/base_single_path_option.h"

namespace OptionPricer {

    class MCSinglePathBuilder final: MCBuilder {
    public:
        using MCBuilder::MCBuilder;
        ~MCSinglePathBuilder() override;

        MCSinglePathBuilder& setOption(std::shared_ptr<Option> option) override;
        std::unique_ptr<MCPricer> build() override;

    private:
        std::shared_ptr<SinglePathOption> option_;
    };

}

#endif //MC_BUILDER_SINGLE_PATH_H
