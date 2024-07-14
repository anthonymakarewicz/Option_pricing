#include <iostream>
#include <memory>
#include "market_data.h"


int main() {
    auto marketdata = MarketData::getInstance();
    auto marketdata2 = MarketData::getInstance();
    if (marketdata == marketdata2) std::cout << "True";
    return 0;
}
