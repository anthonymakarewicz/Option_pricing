#ifndef BASE_PAYOFF_H
#define BASE_PAYOFF_H

#include<memory>

// Abastract base class for Payoff
class Payoff {
public:
    Payoff();
    virtual ~Payoff();

    [[nodiscard]] std::string getType() const;
    [[nodiscard]] virtual std::unique_ptr<Payoff> clone() const = 0; // Prototype creational pattern

    virtual void print(std::ostream& os) const;
    friend std::ostream& operator<<(std::ostream& os, const Payoff& payoff);

    virtual double operator()(const double& S) const = 0; // Define Payoff as a functor
};

#endif //BASE_PAYOFF_H
