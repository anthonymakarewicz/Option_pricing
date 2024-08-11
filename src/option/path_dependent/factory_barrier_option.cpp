#include "option/path_dependent/factory_barrier_option.h"
#include "option/path_dependent/barrier_option.h"
#include "payoff/single_strike/payoff_vanilla.h"
#include "market_data/market_data.h"

namespace OptionPricer {
    // Knock In Factory
    std::unique_ptr<Payoff> KnockInBarrierOptionFactory::createSpecificPayoff(const ParameterObject &params,
        const PayoffType& type) {
        return std::make_unique<PayoffVanilla>(type, params.getParameter<double>("K"));
    }

    std::shared_ptr<Option> KnockInBarrierOptionFactory::createSpecificOption(const ParameterObject &params,
    std::unique_ptr<Payoff> payoff, const std::shared_ptr<IMarketData>& marketData) {
        return std::shared_ptr<Option>(new KnockInBarrierOption(
            params.getParameter<std::string>("ticker"),
            std::move(payoff),
            params.getParameter<double>("T"),
            params.getParameter<double>("B"),
            params.getParameter<BarrierDirection>("direction"),
            marketData
        ));
    }

    // Need to print also the Up/Down characteristic
    std::string KnockInBarrierOptionFactory::getType(const PayoffType& type) const {
        return "Knock-In  " + PayoffTypeToString(type) + " Option";
    }


    // Knock Out Factory
    std::unique_ptr<Payoff> KnockOutBarrierOptionFactory::createSpecificPayoff(const ParameterObject &params,
            const PayoffType& type) {
        return std::make_unique<PayoffVanilla>(type, params.getParameter<double>("K"));
    }

    std::shared_ptr<Option> KnockOutBarrierOptionFactory::createSpecificOption(const ParameterObject &params,
    std::unique_ptr<Payoff> payoff, const std::shared_ptr<IMarketData>& marketData) {
        return std::shared_ptr<Option>(new KnockOutBarrierOption(
        params.getParameter<std::string>("ticker"),
          std::move(payoff),
          params.getParameter<double>("T"),
          params.getParameter<double>("B"),
          params.getParameter<BarrierDirection>("direction"),
          marketData
        ));
    }

    // Need to print also the Up/Down characteristic
    std::string KnockOutBarrierOptionFactory::getType(const PayoffType& type) const {
        return "Knock-Out " + PayoffTypeToString(type) + " Option";
    }
}

