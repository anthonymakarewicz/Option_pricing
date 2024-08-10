#include "option/path_dependent/barrier/factory_up_single_barrier_option.h"
#include "option/path_dependent/barrier/up_single_barrier_option.h"
#include "payoff/single_strike/base_payoff_vanilla.h"
#include <payoff/single_strike/factory_payoff_vanilla.h>
#include <market_data/market_data.h>
/*

namespace OptionPricer {
    std::unique_ptr<Payoff> UpSingleBarrierOptionFactory::createSpecificPayoff(const ParameterObject &params,
            const std::string &type) {
        PayoffVanillaFactory payoffFactory;
        return payoffFactory.createPayoff(type, params.getParameter<double>("K"));
    }

    std::shared_ptr<Option> UpSingleBarrierOptionFactory::createSpecificOption(const ParameterObject &params,
    std::unique_ptr<Payoff> payoff, const std::shared_ptr<IMarketData>& marketData) {
        if
        auto knock = std::make_unique<KnockBehavior>()
        return std::shared_ptr<Option>(new UpSingleBarrierOption(
            params.getParameter<std::string>("ticker"),
            std::move(payoff),
            params.getParameter<double>("T"),
            marketData
        ));
    }

    std::string UpSingleBarrierOptionFactory::getType(const std::string& type) const {
        return "Geometric Asian  " + type + " Option";
    }
}

*/