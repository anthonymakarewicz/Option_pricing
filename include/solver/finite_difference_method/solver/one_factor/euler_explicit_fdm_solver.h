#ifndef EULER_EXPLICIT_FDM_SOLVER_H
#define EULER_EXPLICIT_FDM_SOLVER_H

#include "market_data/interface_market_data.h"
#include "option/single_path/european_option.h"
#include "numerical_analysis/interpolation/base_interpolation.h"
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
                         std::shared_ptr<Interpolation> interpolation = nullptr);

        ~EulerExplicitFDM() override;

    private:
        void calculateInnerDomain() override;
        double alpha, beta, gamma; // Differencing coefficients
    };

}

#endif //EULER_EXPLICIT_FDM_SOLVER_H