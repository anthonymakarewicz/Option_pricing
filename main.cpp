#include <iostream>
#include <option/single_path/european_option.h>
#include "market_data/market_data.h"
#include <payoff/single_strike/payoff_vanilla.h>
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
#include "option/path_dependent/factory_lookback_option.h"
#include "option/path_dependent/factory_american_option.h"

#include "solver/monte_carlo/mc_solver.h"
#include "solver/monte_carlo/builder/mc_builder_american.h"
#include "random/distribution/standard_normal_distribution.h"
#include "random/number_generator/sobol_quasi_random_generator.h"
#include <Eigen/Dense>
#include <model/bates_model.h>
#include <model/heston_model.h>
#include <model/kou_model.h>
#include <model/merton_jump_diffusion_model.h>
#include <model/variance_gamma_model.h>
#include <model/discretization/milstein_cir_discretization.h>
#include <numerical_analysis/linear_algebra/matrix_solver/partial_pivoting_lu_decomposition.h>
#include <numerical_analysis/linear_algebra/matrix_solver/thomas_algorithm.h>
#include <solver/finite_difference_method/pde/one_factor/black_scholes_pde.h>
#include <solver/finite_difference_method/solver/one_factor/euler_explicit_fdm_solver.h>
#include <solver/finite_difference_method/solver/one_factor/euler_implicit_fdm_solver.h>
#include <solver/monte_carlo/mc_single_path.h>
#include <solver/monte_carlo/basis_function/chebyshev.h>
#include <solver/monte_carlo/basis_function/laguerre.h>
#include <solver/monte_carlo/builder/mc_builder_single_path.h>
#include <solver/monte_carlo/regression/lasso.h>
#include <solver/monte_carlo/regression/ridge.h>

#include "numerical_analysis/interpolation/quadratic_interpolation.h"
#include "solver/monte_carlo/basis_function/legendre.h"

using namespace OptionPricer;
using namespace PDE::OneFactor;
using namespace FDM::OneFactor;

int main() {
    std::string ticker = "AAPL";
    double T = 1.0;
    double K = 100.0;
    double S = 100.0;
    double sigma = 0.2;
    double r = 0.05;
    int dim = 1000;

    // Heston parameters
    double kappa = 6.21;
    double theta = 0.019;
    double sigma_v = 0.61;
    double rho = -0.7;
    double v0 = 0.010201;

    // Merton paremeters
    double lambda = 0.1;  // 10% chance of a jump each time step
    double muJ = -0.05;   // Mean jump size (5% downwards)
    double sigmaJ = 0.2;  // Jump size volatility

    // Kou parameters
    double eta1 = 5.0;
    double eta2 = 7.0;
    double p = 0.5;

    // Variance Gamma parameters
    double thetaGamma = -0.05;
    double nu = 0.5;

    auto marketData = MarketData::getInstance();
    marketData->addStock(ticker, S, sigma);
    marketData->setR(r);

    ParameterObject params;
    params.setParameter("ticker", ticker);
    params.setParameter("T", T);
    params.setParameter("K", K);

    auto generator = std::make_shared<SobolGenerator>(dim);
    auto prng = std::make_shared<PseudoRandomNumberGenerator>(dim);
    auto geometricBrownianMotion = std::make_shared<GeometricBrownianMotionModel>(ticker, marketData, generator);
    auto heston = std::make_shared<HestonModel>(ticker, marketData, prng, kappa, theta, sigma_v, rho, v0);
    auto merton = std::make_shared<MertonJumpDiffusionModel>(ticker, marketData, prng, lambda, muJ, sigmaJ);
    auto kou = std::make_shared<KouModel>(ticker, marketData, prng, lambda, p, eta1, eta2);
    auto vg = std::make_shared<VarianceGammaModel>(ticker, marketData, prng, sigma, nu, thetaGamma);
    auto bates = std::make_shared<BatesModel>(ticker, marketData, prng, kappa, theta, sigma_v, rho, v0, lambda, muJ, sigmaJ);
    auto laguerre = std::make_shared<LaguerreBasisFunction>(3);
    auto regression = std::make_shared<LeastSquaresRegression>();

    AmericanOptionFactory factory;
    auto americanPut = factory.createPutOption(params);

    AmericanMCBuilder builder;
    auto americanPricer = builder.setOption(americanPut)
                                 .setBasisFunctionStrategy(laguerre)
                                 .setStockPriceModel(heston)
                                 .build();

    EuropeanOptionFactory factoryEuropean;
    auto europeanCall = factoryEuropean.createCallOption(params);

    MCSinglePathBuilder singlePathBuilder;
    auto singlePathPricer = singlePathBuilder.setOption(europeanCall).setStockPriceModel(geometricBrownianMotion).build();

    MCSolver mcSolver;
    mcSolver.setN(300000);
    mcSolver.setPricer(std::move(singlePathPricer));


    //std::cout << "Price MC: " << mcSolver.solve() << "\n";

    /*
    int N = 50;

    for (int i = 0; i < N; i++) {
        std::cout << "Price at T Merton: " << merton->simulatePriceAtMaturity(T) << std::endl;
    }

    for (int i = 0; i < N; i++) {
        std::cout << "Price at T Heston: " << heston->simulatePriceAtMaturity(T) << std::endl;
    }

    for (int i = 0; i < N; i++) {
        std::cout << "Price at T Kou: " << kou->simulatePriceAtMaturity(T)<< std::endl;
    }

    for (int i = 0; i < N; i++) {
        std::cout << "Price at T VG: " << vg->simulatePriceAtMaturity(T)<< std::endl;
    }

    for (int i = 0; i < N; i++) {
        std::cout << "Price at T Bates: " << bates->simulatePriceAtMaturity(T)<< std::endl;
    }
    */

    double xDom = 2.0 * K; // Spot goes from [0.0 , 1.0]
    unsigned long J = 40;
    double tDom = T; // Time period as for the option
    unsigned long N2 = 40;
    auto pde = std::make_unique<BlackScholesPDE>(europeanCall, marketData);
    auto pde2 = std::make_unique<BlackScholesPDE>(europeanCall, marketData);
    auto thomas = std::make_shared<ThomasAlgorithm>();
    auto partialPiv = std::make_shared<PartialPivotingLUSolver>();

    auto quadrInterp = std::make_shared<QuadraticInterpolation>();
    EulerExplicitFDM fdm(xDom, J, tDom, N2, std::move(pde), europeanCall, marketData, quadrInterp);
    EulerImplicitFDM fdm2(xDom, J, tDom, N2, std::move(pde2), europeanCall, marketData, quadrInterp, partialPiv);
    auto prices = fdm.solve();

    //for (const auto& price : prices)
    //    std::cout << "Price: " << price << std::endl;

    std::cout << "FDM price Explicit: " << fdm.calculatePrice() << std::endl;

    std::cout << "FDM price Implicit: " << fdm2.calculatePrice() << std::endl;

    /*
    std::cout << "S = 100, dim = 50, P = ";
    std::cout << mcSolver.solve() << "\n";
    */


    return 0;
    /*
    marketData->updateStockPrice(ticker, 90);
    auto americanPricer2 = builder.build();
    mcSolver.setPricer(std::move(americanPricer2));

    std::cout << "S = 90, dim = 50, P = ";
    std::cout << mcSolver.solve() << "\n";
    return 0;
    */
    /*
    marketData->updateStockPrice(ticker, 110);
    auto americanPricer3 = builder.build();

    mcSolver.setPricer(std::move(americanPricer3));
    std::cout << "S = 110, dim = 50, P = ";
    std::cout << mcSolver.solve() << "\n";
    */
    /*
    dim = 100;
    marketData->updateStockPrice("AAPL", 100);
    auto generator2 = std::make_shared<SobolGenerator>(normal, dim);
    auto americanPricer4 = builder.setSteps(dim).setNumberGenerator(generator2).build();

    std::cout << "S = 100, dim = 100, P = ";
    mcSolver.setPricer(std::move(americanPricer4));
    std::cout << mcSolver.solve() << "\n";

    marketData->updateStockPrice("AAPL", 90);
    auto americanPricer5 = builder.build();

    mcSolver.setPricer(std::move(americanPricer5));
    std::cout << "S = 90, dim = 100, P = ";
    std::cout << mcSolver.solve() << "\n";

    marketData->updateStockPrice("AAPL", 110);
    auto americanPricer6 = builder.build();

    mcSolver.setPricer(std::move(americanPricer6));
    std::cout << "S = 110, dim = 100, P = ";
    std::cout << mcSolver.solve() << "\n";
    */

}