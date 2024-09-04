#ifndef BLACK_SCHOLES_PDE_H
#define BLACK_SCHOLES_PDE_H

#include "option/single_path/european_option.h"
#include "solver/finite_difference_method/pde/one_factor/base_convection_diffusion_pde.h"

namespace OptionPricer::PDE::OneFactor {

    class BlackScholesPDE : public ConvectionDiffusionPDE {
    public:
        BlackScholesPDE(std::shared_ptr<EuropeanOption> option, std::shared_ptr<IMarketData> marketData);
        virtual ~BlackScholesPDE();

        double diffusion(const double& t,const double& x) const override;
        double convection(const double& t,const double& x) const override;
        double reaction(const double& t,const double& x) const override;
        double rightHandSide(const double& t,const double& x) const override;

        double boundaryLeft(const double& t,const double& x) const override;
        double boundaryRight(const double& t,const double& x) const override;
        double initialCondition(const double& x) const override;

    private:
        std::shared_ptr<EuropeanOption> option_;
        std::shared_ptr<IMarketData> marketData_;
    };

}

#endif //BLACK_SCHOLES_PDE_H
