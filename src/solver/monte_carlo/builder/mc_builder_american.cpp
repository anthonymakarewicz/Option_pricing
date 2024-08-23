#include "solver/monte_carlo/builder/mc_builder_american.h"

namespace OptionPricer {

    AmericanMCBuilder::AmericanMCBuilder()
    : MCBuilder(), regressionStrategy_(std::make_shared<LeastSquaresRegression>()),
    basisFunctionStrategy_(std::make_shared<MonomialBasisFunction>(3)) {}

    AmericanMCBuilder::~AmericanMCBuilder() = default;

    AmericanMCBuilder& AmericanMCBuilder::setOption(std::shared_ptr<Option> option) {
        option_ = std::dynamic_pointer_cast<AmericanOption>(option);
        if (!option_) {
            throw std::invalid_argument("Invalid option type for AmericanMCBuilder");
        }
        return *this;
    }

    AmericanMCBuilder& AmericanMCBuilder::setRegressionStrategy(std::shared_ptr<RegressionStrategy> regressionStrategy) {
        regressionStrategy_ = std::move(regressionStrategy);
        return *this;
    }

    AmericanMCBuilder& AmericanMCBuilder::setBasisFunctionStrategy(std::shared_ptr<BasisFunctionStrategy> basisFunctionStrategy) {
        basisFunctionStrategy_ = std::move(basisFunctionStrategy);
        return *this;
    }

    std::unique_ptr<MCPricer> AmericanMCBuilder::build() {
        if (!option_) throw std::logic_error("Option is not set for AmericanMCBuilder.");
        if (!stockModel_) {
            stockModel_ = std::make_shared<GeometricBrownianMotionModel>(option_->getID(),
                                                                         marketData_,
                                                                         std::make_shared<PseudoRandomNumberGenerator>(52));
        }
        return std::make_unique<AmericanMCPricer>(option_, marketData_, stockModel_,
                                                  basisFunctionStrategy_, regressionStrategy_);
    }

}
