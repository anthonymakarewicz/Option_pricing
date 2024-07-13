#include <iostream>
#include "option.h"
#include "payoff.h"
#include "market_data.h"

int main() {
    StockData stock(100.0, 0.02, 0.001);
    std::cout << stock.getSigma() << std::endl;

    auto mdata = std::make_shared<MarketData>();
    mdata->addData<StockData>("AAPL", 100.0, 0.02, 0.01);

    auto payoff_call = std::make_unique<PayoffCall>(100.0);
    auto payoff_put = std::make_unique<PayoffPut>(100.0);


    auto mdata = std::make_shared<MarketData>();
    mdata->addData<StockData>("AAPL", 300.0, 0.24, 0.01);
    mdata->addData<StockData>("AMAZN", 120.0, 0.2, 0.01);
    mdata->addData<StockData>("TSLA", 70.0, 0.3, 0.01);
    mdata->addData<InterestRateData>("LIBOR", 0.02);
    mdata->addData<InterestRateData>("EURIBIBOR", 0.03);
    mdata->addData<FXRateData>("GBP", 1.25);
    mdata->addData<FXRateData>("EUR", 1.05);

    std::vector<std::string>> underlyings_basket = {"AAPL", "AMAZN", "TSLA"};
    std::vector<std::string>> underlyings_quanto = {"AAPL", "GBP"};

    Option call(std::move(payoff_call), mdata, S = "AAPL", r = "LIBOR");
    BasketOption call_basket(std::move(payoff_basket_call), mdata, S = underlyings_basket, r = "LIBOR");
    QuantoOption call_quanto(std::move(payoff_quanto_call), mdata, S = underlyings_quanto, r = "LIBOR");







    return 0;
}
