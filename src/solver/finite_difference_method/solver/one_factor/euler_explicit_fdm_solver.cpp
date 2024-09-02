#include "solver/finite_difference_method/solver/one_factor/euler_explicit_fdm_solver.h"
#include "solver/finite_difference_method/solver/one_factor/interpolation/linear_interpolation.h"

namespace OptionPricer::FDM::OneFactor {
    EulerExplicitFDM::EulerExplicitFDM(const double &xDom, const unsigned long &J,
                                       const double &tDom, const unsigned long &N,
                                       std::unique_ptr<ConvectionDiffusionPDE> pde,
                                       std::shared_ptr<EuropeanOption> option,
                                       std::shared_ptr<IMarketData> marketData,
                                       std::shared_ptr<InterpolationStrategy> interpolation)
    : FDMSolver(xDom, J, tDom, N, std::move(pde)), marketData_(std::move(marketData)), option_(std::move(option)),
      alpha(0.0), beta(0.0), gamma(0.0), solved(false) {
        if (!interpolation)
            interpolation_ = std::make_shared<LinearInterpolation>();
        else
            interpolation_ = std::move(interpolation);
    }

    double EulerExplicitFDM::calculatePrice() {
        solve();
        const double S = marketData_->getStockData(option_->getID())->getPrice();
        return interpolation_->interpolate(newPrices, xValues, S);
    }

    void EulerExplicitFDM::calculateInnerDomain() {
        for (unsigned long j = 1; j < (J_-1); j++) {
            // Temporary variables
            const double dtSig = dt * pde_->diffusion(tPrev, xValues[j]);
            const double dtSig2 = 0.5 * dt*dx * pde_->convection(tPrev, xValues[j]);

            // Differencing coefficients
            alpha = dtSig - dtSig2;
            beta = dx*dx - (2.0 * dtSig) + (dt * dx*dx * (pde_->reaction(tPrev, xValues[j])));
            gamma= dtSig + dtSig2;

            // Explicit Euler discretization scheme
            newPrices[j] = ((alpha*oldPrices[j-1]) + (beta*oldPrices[j]) + (gamma*oldPrices[j+1])) / (dx*dx)
            - (dt*(pde_->rightHandSide(tPrev, xValues[j])));
        }
    }
}
