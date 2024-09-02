#ifndef EULER_EXPLICIT_FDM_SOLVER_H
#define EULER_EXPLICIT_FDM_SOLVER_H

#include <market_data/interface_market_data.h>
#include <option/single_path/european_option.h>

#include "interpolation/base_interpolation_strategy.h"
#include "solver/finite_difference_method/pde/one_factor/base_convection_diffusion_pde.h"
#include "solver/finite_difference_method/solver/one_factor/base_fdm_solver.h"

namespace OptionPricer::FDM::OneFactor {

    using namespace PDE::OneFactor;

    class EulerExplicitFDM final : public FDMSolver {
    public:
        EulerExplicitFDM(const double &xDom, const unsigned long &J,
                         const double &tDom, const unsigned long &N,
                         std::unique_ptr<ConvectionDiffusionPDE> pde,
                         std::shared_ptr<EuropeanOption> option,
                         std::shared_ptr<IMarketData> marketData,
                         std::shared_ptr<InterpolationStrategy> interpolation = nullptr);
        double calculatePrice();

    private:
        void calculateInnerDomain() override;

        bool solved;
        double alpha, beta, gamma; // Differencing coefficients
        std::shared_ptr<IMarketData> marketData_;
        std::shared_ptr<EuropeanOption> option_;
        std::shared_ptr<InterpolationStrategy> interpolation_;
    };

}

#endif //EULER_EXPLICIT_FDM_SOLVER_H