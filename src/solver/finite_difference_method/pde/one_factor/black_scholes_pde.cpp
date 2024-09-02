#include "solver/finite_difference_method/pde/one_factor/black_scholes_pde.h"

#include <payoff/single_strike/base_payoff_single_strike.h>

namespace OptionPricer::PDE::OneFactor {
    BlackScholesPDE::BlackScholesPDE(std::shared_ptr<EuropeanOption> option, std::shared_ptr<IMarketData> marketData)
    : option_(std::move(option)), marketData_(std::move(marketData)) {}

    BlackScholesPDE::~BlackScholesPDE() = default;

    double BlackScholesPDE::diffusion(const double &t, const double &x) const {
        const double sigma = marketData_->getStockData(option_->getID())->getSigma();
        return 0.5 * sigma*sigma * x*x;
    }

    double BlackScholesPDE::convection(const double &t, const double &x) const {
        const double c =  marketData_->getStockData(option_->getID())->getCoupon().value_or(0.0);
        const double r = marketData_->getR();
        return (r - c) * x;
    }

    double BlackScholesPDE::reaction(const double &t, const double &x) const {
        const double r = marketData_->getR();
        return -r;
    }

    double BlackScholesPDE::rightHandSide(const double &t, const double &x) const {
        return 0.0;
    }

    double BlackScholesPDE::boundaryLeft(const double &t, const double &x) const {
        const std::shared_ptr<Payoff> clonedPayoff = option_->getPayoff().clone();
        const auto payoff = std::dynamic_pointer_cast<PayoffSingleStrike>(clonedPayoff);
        if (!payoff) {
            throw std::invalid_argument("Option payoff is not present");
        }
        if (option_->getPayoff().getPayoffType() == PayoffType::Call) {
            return 0.0;
        }

        return payoff->getK();
    }

    double BlackScholesPDE::boundaryRight(const double &t, const double &x) const {
        const std::shared_ptr<Payoff> clonedPayoff = option_->getPayoff().clone();
        const auto payoff = std::dynamic_pointer_cast<PayoffSingleStrike>(clonedPayoff);
        if (!payoff) {
            throw std::invalid_argument("Option payoff is not present");
        }
        if (option_->getPayoff().getPayoffType() == PayoffType::Call) {
            const double K = payoff->getK();
            const double r = marketData_->getR();
            const double T = option_->getT();
            return x - K * std::exp(-r * (T - t));
        }

        return 0.0;
    }

    double BlackScholesPDE::initialCondition(const double &x) const {
        return option_->payoff(x);
    }

}
