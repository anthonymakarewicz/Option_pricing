#include "solver/monte_carlo/builder/mc_builder_barrier.h"
#include "solver/monte_carlo/mc_barrier.h"

namespace OptionPricer {

    // Knock-In
    KnockInBarrierMCBuilder& KnockInBarrierMCBuilder::setOption(std::shared_ptr<Option> option) {
        option_ = std::dynamic_pointer_cast<KnockInBarrierOption>(option);
        if (!option_) {
            throw std::invalid_argument("Invalid option type for KnockInBarrierMCPricerBuilder");
        }
        return *this;
    }

    std::unique_ptr<MCPricer> KnockInBarrierMCBuilder::build() {
        if (!option_) throw std::logic_error("Option is not set for KnockInBarrierMCPricerBuilder.");
        if (!stockModel_) {
            stockModel_ = std::make_shared<GeometricBrownianMotionModel>(option_->getID(),
                                                                         marketData_,
                                                                         std::make_shared<PseudoRandomNumberGenerator>(52));
        }
        return std::make_unique<KnockInBarrierMCPricer>(option_, marketData_, stockModel_);
    }

    // Knock-Out
    KnockOutBarrierMCBuilder& KnockOutBarrierMCBuilder::setOption(std::shared_ptr<Option> option) {
        option_ = std::dynamic_pointer_cast<KnockOutBarrierOption>(option);
        if (!option_) {
            throw std::invalid_argument("Invalid option type for KnockOutBarrierMCPricerBuilder");
        }
        return *this;
    }

    std::unique_ptr<MCPricer> KnockOutBarrierMCBuilder::build() {
        if (!option_) throw std::logic_error("Option is not set for KnockOutBarrierMCPricerBuilder.");
        if (!stockModel_) {
            stockModel_ = std::make_shared<GeometricBrownianMotionModel>(option_->getID(),
                                                                         marketData_,
                                                                         std::make_shared<PseudoRandomNumberGenerator>(52));
        }
        return std::make_unique<KnockOutBarrierMCPricer>(option_, marketData_, stockModel_);
    }

}
