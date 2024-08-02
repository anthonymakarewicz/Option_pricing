#include <iostream>
#include <option/single_path/european_option.h>
#include <market_data/market_data.h>
#include <payoff/single_strike/payoff_vanilla_call.h>
#include <option/single_path/factory_european_option.h>

using namespace OptionPricer;

int main() {
    auto marketData = MarketData::getInstance();
    marketData->addStock("AAPL", 120.0, 0.2);

    ParameterObject params;
    params.setParameter("ticker", "AAPL");
    params.setParameter("T", 1.0);
    params.setParameter("K", 100.0);

    EuropeanOptionFactory factory;
    try {
        auto option = factory.createCallOption(params);
    } catch (const std::exception& e) {
        std::cerr << e.what();
    }
    auto option2 = factory.createCallOption(params);


    return 0;

    /*
    auto marketData = MarketData::getInstance();
    marketData->addStock("AAPL", 120.0, 0.2);

    double K = 100.0;
    auto payoff = std::make_unique<PayoffVanillaCall>(K);
    double T = 1.0;

    auto option = std::make_shared<EuropeanOption>("AAPL", std::move(payoff), T, marketData);
    option->initialize();
    std::cout << *option;
    */

    return 0;

}