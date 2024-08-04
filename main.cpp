#include <iostream>
#include <option/single_path/european_option.h>
#include <market_data/market_data.h>
#include <payoff/single_strike/payoff_vanilla_call.h>
#include <option/single_path/factory_european_option.h>
#include <option/single_path/factory_double_digital_option.h>
#include <boost/random/sobol.hpp>
#include <iomanip>
#include <vector>
#include <fstream>
#include <filesystem>

using namespace OptionPricer;

int main() {
    boost::random::sobol qrng(2); // 3-dimensional Sobol sequence
    qrng.seed(42);
    std::vector<double> point(2);
    std::cout << std::filesystem::current_path();

    std::ofstream csvFile("../examples/sobol_sequence_5.csv");
    if (!csvFile.is_open()) {
        std::cerr << "Failed to open file for writing." << std::endl;
        return 1;
    }

    csvFile << "x,y\n";

    std::cout << "Sobol sequence using Boost:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        qrng.generate(point.begin(), point.end());
        for (auto& coord : point)
            coord /= static_cast<double>(boost::random::sobol::max());

        csvFile << std::fixed << std::setprecision(8) << point[0] << "," << point[1] << "\n";
        std::cout << std::endl;
    }
    csvFile.close();

    return 0;

    /*
    auto marketData = MarketData::getInstance();
    marketData->addStock("AAPL", 120.0, 0.2);

    ParameterObject params;
    params.setParameter("ticker", "AAPL");
    params.setParameter("T", 1.0);
    params.setParameter("K1", 100.0);
    params.setParameter("K2", 120.0);

    DoubleDigitalOptionFactory factory;
    try {
        auto option = factory.createCallOption(params);
    } catch (const std::exception& e) {
        std::cerr << e.what();
    }
    std::cout << "ded";

    auto marketData = MarketData::getInstance();
    marketData->addStock("AAPL", 120.0, 0.2);

    double K = 100.0;
    auto payoff = std::make_unique<PayoffVanillaCall>(K);
    double T = 1.0;

    auto option = std::make_shared<EuropeanOption>("AAPL", std::move(payoff), T, marketData);
    option->initialize();
    std::cout << *option;


    return 0;
    */
}