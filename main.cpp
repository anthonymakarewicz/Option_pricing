#include <iostream>
#include <option/single_path/european_option.h>
#include "market_data/market_data.h"
#include <payoff/single_strike/payoff_vanilla_call.h>
#include <option/single_path/factory_european_option.h>
#include "option/single_path/factory_double_digital_option.h"
#include <boost/random/sobol.hpp>
#include <iomanip>
#include <vector>
#include <fstream>
#include <filesystem>
#include <option/single_path/factory_digital_option.h>
#include "option/path_dependent/factory_asian_option.h"
#include "option/path_dependent/factory_barrier_option.h"



#include "solver/monte_carlo/mc_solver.h"
#include "solver/monte_carlo/gbm_stock_price_model.h"

using namespace OptionPricer;

int main() {
    std::string ticker = "AAPL";
    double T = 1.0;
    double K = 100.0;
    double S = 100.0;
    double sigma = 0.2;
    double r = 0.05;
    double B = 120;
    double dim = 52;
    auto marketData = MarketData::getInstance();
    marketData->addStock(ticker, S, sigma);
    marketData->setR(r);

    ParameterObject params;
    params.setParameter("ticker", "AAPL");
    params.setParameter("T", T);
    params.setParameter("K", K);
    params.setParameter("B", B);
    params.setParameter("direction", BarrierDirection::Up);

    KnockInBarrierOptionFactory factory;
    auto call = factory.createCallOption(params);

    auto normal = std::make_shared<StandardNormalDistribution>();
    auto generator = std::make_shared<SobolGenerator>(normal, dim);
    auto brownianMotion = std::make_shared<BrownianMotionModel>(ticker, marketData);
    auto mcStrategy = std::make_unique<KnockInMCStrategy>(call, brownianMotion, generator, marketData, dim);


    MCSolver mcSolver;
    mcSolver.setN(500000);
    mcSolver.setStrategy(std::move(mcStrategy));

    std::cout << mcSolver.solve();

    //std::vector<unsigned long> Ns = {100, 1000, 10000, 100000, 1000000, 10000000};


    return 0;
    /*
    std::cout << "Crude MC Call:" << std::endl;
    for (const auto& N : Ns) {
        mcSolver.setN(N);
        auto mcStrategy = std::make_unique<SinglePathMCStrategy>(call, brownianMotion, generator, marketData);
        mcSolver.setStrategy(std::move(mcStrategy));
        std::cout << "N = " << N << ", Price: " << mcSolver.solve() << "\n";
    }

    auto put = factory.createPutOption(params);

    std::cout << "Crude MC Put:" << std::endl;
    for (const auto& N : Ns) {
        mcSolver.setN(N);
        auto mcStrategy = std::make_unique<SinglePathMCStrategy>(put, brownianMotion, generator, marketData);
        mcSolver.setStrategy(std::move(mcStrategy));
        std::cout << "N = " << N << ", Price: " << mcSolver.solve() << "\n";
    }

    auto generator2 = std::make_shared<SobolGenerator>(normal);

    std::cout << "Quasi MC Sobol:" << std::endl;
    for (const auto& N : Ns) {
        mcSolver.setN(N);
        auto mcStrategy = std::make_unique<SinglePathMCStrategy>(call, brownianMotion, generator2, marketData);
        mcSolver.setStrategy(std::move(mcStrategy));
        std::cout << "N = " << N << ", Price: " << mcSolver.solve() << "\n";
    }

    auto generator3 = std::make_shared<FaureGenerator>(normal);

    std::cout << "Quasi MC Faure:" << std::endl;
    for (const auto& N : Ns) {
        mcSolver.setN(N);
        auto mcStrategy = std::make_unique<SinglePathMCStrategy>(call, brownianMotion, generator3, marketData);
        mcSolver.setStrategy(std::move(mcStrategy));
        std::cout << "N = " << N << ", Price: " << mcSolver.solve() << "\n";
    }

    return 0;

    */

    /*
auto mcStrategy = std::make_unique<SinglePathMCStrategy>(eurCall, brownianMotion, generator, marketData);
mcSolver.setStrategy(std::move(mcStrategy));
std::cout << "Crude: " << mcSolver.solve() << "\n";

auto generator2 = std::make_shared<FaureGenerator>(normal);
mcStrategy = std::make_unique<SinglePathMCStrategy>(eurCall, brownianMotion, generator2, marketData);
mcSolver.setStrategy(std::move(mcStrategy));
std::cout << "Faure: " << mcSolver.solve() << "\n";
*/

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

    */


}