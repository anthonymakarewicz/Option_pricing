#ifndef BASE_FDM_SOLVER_H
#define BASE_FDM_SOLVER_H

#include <vector>
#include "market_data/interface_market_data.h"
#include "option/single_path/european_option.h"
#include "numerical_analysis/interpolation/base_interpolation.h"
#include "solver/finite_difference_method/pde/one_factor/base_convection_diffusion_pde.h"

namespace OptionPricer::FDM::OneFactor {

    using namespace PDE::OneFactor;
    using namespace FDM::OneFactor;

    class FDMSolver {
    protected:
        FDMSolver(const double& xDom, const unsigned long& J,
                  const double& tDom, const unsigned long& N,
                  std::unique_ptr<ConvectionDiffusionPDE> pde,
                  std::shared_ptr<EuropeanOption> option,
                  std::shared_ptr<IMarketData> marketData,
                  std::shared_ptr<Interpolation> interpolation);

        // Invariant parts
        void calculateStepSizes();
        void calculateInitialConditions ();

        // Variant part
        virtual void calculateBoundaryConditions() = 0;
        virtual void calculateInnerDomain() = 0;

        // Space discretisation
        double xDom_;      // Spatial domain [0.0 , xDom]
        unsigned long J_; // Number of spatial differencing points
        double dx, dx2;       // Pre calculated spatial step size
        std::vector<double> xValues ; // Stores all values

        // Time discretisation
        double tDom_ ;     // Temporal domain [0.0 , tDom]
        unsigned long N_; // Number of temporal differencing points
        double dt;       // Pre calculated temporal step size

        // Time−marching
        double tPrev , tCurr ; // Current and previous times

        // Storage
        std::vector<double> newPrices;
        std::vector<double> oldPrices;

        bool solved;

        // Attributes
        std::unique_ptr<ConvectionDiffusionPDE> pde_;
        std::shared_ptr<IMarketData> marketData_;
        std::shared_ptr<EuropeanOption> option_;
        std::shared_ptr<Interpolation> interpolation_;

    public:
        virtual ~FDMSolver();

        std::vector<double> solve(); // Could return a matrix of prices for all time steps
        double calculatePrice();     // Return the option price given the current stock price
    };

}

#endif //BASE_FDM_SOLVER_H