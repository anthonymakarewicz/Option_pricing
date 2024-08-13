#include "solver/monte_carlo/builder/mc_builder_single_path.h"

namespace OptionPricer {

    MCSinglePathBuilder::~MCSinglePathBuilder() = default;

    MCSinglePathBuilder & MCSinglePathBuilder::setOption(std::shared_ptr<Option> option) {
        option_ = std::dynamic_pointer_cast<SinglePathOption>(option);
        if (!option_) {
            throw std::invalid_argument("Invalid option type for AmericanMCPricerBuilder");
        }
        return *this;
    }

    std::unique_ptr<MCPricer> MCSinglePathBuilder::build() {
        if (!option_) throw std::logic_error("Option is not set for AmericanMCPricerBuilder.");
        if (!stockModel_) {
            stockModel_ = std::make_unique<BrownianMotionModel>(option_->getID(), marketData_);
        }
        return std::make_unique<SinglePathMCPricer>(option_, marketData_, stockModel_, generator_);
    }

}
