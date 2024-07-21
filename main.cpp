
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
    /*
    auto pc3 = std::make_unique<PayoffCall>(100);
    auto option2 = std::make_shared<Option>("AAPL", std::move(pc3), 1.0);
    std::cout << "C" << std::endl;
    //auto option = std::make_shared<Option>();
    std::cout << "D" << std::endl;
    option2->initialize();
    std::cout << "E" << std::endl;
    */
    return 0;

}




