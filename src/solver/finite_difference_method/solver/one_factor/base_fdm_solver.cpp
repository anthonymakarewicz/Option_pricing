#include "solver/finite_difference_method/solver/one_factor/base_fdm_solver.h"
#include "numerical_analysis/interpolation/linear_interpolation.h"
#include <iostream>

namespace OptionPricer::FDM::OneFactor {

    FDMSolver::FDMSolver(const double &xDom, const unsigned long &J,
                         const double &tDom, const unsigned long &N,
                         std::unique_ptr<ConvectionDiffusionPDE> pde,
                         std::shared_ptr<EuropeanOption> option,
                         std::shared_ptr<IMarketData> marketData,
                         std::shared_ptr<Interpolation> interpolation)
    : xDom_(xDom), J_(J), tDom_(tDom), N_(N),
    pde_(std::move(pde)), option_(std::move(option)), marketData_(std::move(marketData)),
      tPrev(0.0), tCurr(0.0), solved(false){
        calculateStepSizes();
        calculateInitialConditions();

        if (dt / (dx*dx) >= 0.5)
            std::cerr << "CFL condition not satisfied!\nThe solution could be unstable";

        if (!interpolation)
            interpolation_ = std::make_shared<LinearInterpolation>();
        else
            interpolation_ = std::move(interpolation);
    }

    FDMSolver::~FDMSolver() = default;

    void FDMSolver::calculateStepSizes() {
        dx = xDom_ / static_cast<double>(J_-1);
        dt = tDom_ / static_cast<double>(N_-1);
        dx2 = dx*dx;
    }

    void FDMSolver::calculateInitialConditions() {
        double currS = 0.0;
        oldPrices.resize(J_, 0.0); newPrices.resize(J_, 0.0);
        xValues.resize(J_, 0.0);

        for (unsigned long j = 0; j < J_; j++) {
            currS = static_cast<double>(j) * dx;
            oldPrices[j] = pde_->initialCondition(currS);
            xValues[j] = currS;
        }
    }

    void FDMSolver::calculateBoundaryConditions() {
        newPrices.front() = pde_->boundaryLeft(tPrev, xValues.front()) ;
        newPrices.back() = pde_->boundaryRight(tPrev, xValues.back()) ;
    }

    std::vector<double> FDMSolver::solve() {
        while(tCurr < tDom_) {
            tCurr = tPrev + dt;
            calculateBoundaryConditions();
            calculateInnerDomain(); // To be overiden in concrete classes
            oldPrices = newPrices;
            tPrev = tCurr;
        }
        solved = true;
        return newPrices;
    }

    double FDMSolver::calculatePrice() {
        if (!solved) solve();
        const double S = marketData_->getStockData(option_->getID())->getPrice();
        return interpolation_->interpolate(xValues, newPrices, S);
    }

}
