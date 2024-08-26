#ifndef BASE_CONVECTION_DIFFUSION_PDE_H
#define BASE_CONVECTION_DIFFUSION_PDE_H

namespace OptionPricer::PDE::OneFactor {

    class ConvectionDiffusionPDE {
    public:
        virtual ~ConvectionDiffusionPDE();

        virtual double diffusion(const double& t,const double& x) const = 0;
        virtual double convection(const double& t,const double& x) const = 0;
        virtual double reaction(const double& t,const double& x) const = 0;
        virtual double rightHandSide(const double& t,const double& x)const = 0;

        virtual double boundaryLeft(const double& t,const double& x)const = 0;
        virtual double boundaryRight(const double& t,const double& x)const = 0;
        virtual double initialCondition(const double& x) const = 0;
    };

}

#endif //BASE_CONVECTION_DIFFUSION_PDE_H