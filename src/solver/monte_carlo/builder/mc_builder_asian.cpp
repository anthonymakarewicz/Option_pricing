#include "solver/monte_carlo/builder/mc_builder_asian.h"

namespace OptionPricer {

    // Arithmetic Asian
    ArithmeticAsianMCBuilder& ArithmeticAsianMCBuilder::setOption(std::shared_ptr<Option> option) {
        option_ = std::dynamic_pointer_cast<ArithmeticAsianOption>(option);
        if (!option_) {
            throw std::invalid_argument("Invalid option type for ArithmeticAsianMCPricerBuilder");
        }
        return *this;
    }

    std::unique_ptr<MCPricer> ArithmeticAsianMCBuilder::build() {
        if (!option_) throw std::logic_error("Option is not set for ArithmeticAsianMCPricerBuilder.");
        if (!stockModel_) {
            stockModel_ = std::make_shared<GeometricBrownianMotionModel>(option_->getID(),
                                                                         marketData_,
                                                                         std::make_shared<PseudoRandomNumberGenerator>(52));
        }
        return std::make_unique<ArithmeticAsianMCPricer>(option_, marketData_, stockModel_);
    }

    // Geometric Asian
    GeometricAsianMCBuilder& GeometricAsianMCBuilder::setOption(std::shared_ptr<Option> option) {
        option_ = std::dynamic_pointer_cast<GeometricAsianOption>(option);
        if (!option_) {
            throw std::invalid_argument("Invalid option type for GeometricAsianMCPricerBuilder");
        }
        return *this;
    }

    std::unique_ptr<MCPricer> GeometricAsianMCBuilder::build() {
        if (!option_) throw std::logic_error("Option is not set for GeometricAsianMCPricerBuilder.");
        if (!stockModel_) {
            stockModel_ = std::make_shared<GeometricBrownianMotionModel>(option_->getID(),
                                                                         marketData_,
                                                                         std::make_shared<PseudoRandomNumberGenerator>(52));
        }
        return std::make_unique<GeometricAsianMCPricer>(option_, marketData_, stockModel_);
    }

}
