#include "solver/monte_carlo/builder/mc_builder_lookback.h"

namespace OptionPricer {

    // Floating Strike
    FloatingStrikeLookbackMCBuilder::~FloatingStrikeLookbackMCBuilder() = default;

    FloatingStrikeLookbackMCBuilder& FloatingStrikeLookbackMCBuilder::setOption(std::shared_ptr<Option> option) {
        option_ = std::dynamic_pointer_cast<FloatingStrikeLookbackOption>(option);
        if (!option_) {
            throw std::invalid_argument("Invalid option type for FloatingStrikeLookbackMCBuilder");
        }
        return *this;
    }

    std::unique_ptr<MCPricer> FloatingStrikeLookbackMCBuilder::build() {
        if (!option_) throw std::logic_error("Option is not set for FloatingStrikeLookbackMCBuilder.");
        if (!stockModel_) {
            stockModel_ = std::make_shared<GeometricBrownianMotionModel>(option_->getID(), marketData_);
        }
        return std::make_unique<FloatingStrikeLookbackMCPricer>(option_, marketData_, stockModel_, generator_, steps_);
    }

    // Fixed Strike
    FixedStrikeLookbackMCBuilder::~FixedStrikeLookbackMCBuilder() = default;

    FixedStrikeLookbackMCBuilder& FixedStrikeLookbackMCBuilder::setOption(std::shared_ptr<Option> option) {
        option_ = std::dynamic_pointer_cast<FixedStrikeLookbackOption>(option);
        if (!option_) {
            throw std::invalid_argument("Invalid option type for FixedStrikeLookbackMCBuilder");
        }
        return *this;
    }

    std::unique_ptr<MCPricer> FixedStrikeLookbackMCBuilder::build() {
        if (!option_) throw std::logic_error("Option is not set for FixedStrikeLookbackMCBuilder.");
        if (!stockModel_) {
            stockModel_ = std::make_shared<GeometricBrownianMotionModel>(option_->getID(), marketData_);
        }
        return std::make_unique<FixedStrikeLookbackMCPricer>(option_, marketData_, stockModel_, generator_, steps_);
    }

}