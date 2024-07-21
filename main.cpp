
#include <iostream>
#include "option.h"

int main() {

    auto marketdata = MarketData::getInstance();
    marketdata->addStock("AAPL", 100.0, 0.2);

    auto pc = std::make_unique<PayoffCall>(100);
    std::cout << "A" << std::endl;
    VanillaOptionFactory factory;
    std::cout << "B" << std::endl;

    auto vanilla = factory.createOption("AAPL", std::move(pc), 1.0);
    std::cout << vanilla.get() << std::endl;
    std::cout << "C" << std::endl;
    return 0;
    /*
    void MarketData::removeObserver() {
        // Erase_if introduced in C++20 that replace the erase-remove idiom
        std::erase_if(observers_, [&observer](const std::weak_ptr<MarketDataObserver>& obs) {
            return obs.expired();
        });
    }
    */

}