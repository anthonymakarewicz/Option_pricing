#ifndef BLACK_SCHOLES_PDE_H
#define BLACK_SCHOLES_PDE_H

#include "option/single_path/european_option.h"
#include "solver/finite_difference_method/pde/one_factor/base_convection_diffusion_pde.h"

namespace OptionPricer::PDE::OneFactor {

    class BlackScholesPDE : public ConvectionDiffusionPDE {
    public:
        BlackScholesPDE(std::shared_ptr<EuropeanOption> option, std::shared_ptr<IMarketData> marketData);
        virtual ~BlackScholesPDE();

        virtual double diffusion(const double& t,const double& x) const;
        virtual double convection(const double& t,const double& x) const;
        virtual double reaction(const double& t,const double& x) const;
        virtual double rightHandSide(const double& t,const double& x) const;

        virtual double boundaryLeft(const double& t,const double& x) const;
        virtual double boundaryRight(const double& t,const double& x) const;
        virtual double initialCondition(const double& x) const;

    private:
        std::shared_ptr<EuropeanOption> option_;
        std::shared_ptr<IMarketData> marketData_;
    };

}

#endif //BLACK_SCHOLES_PDE_H
