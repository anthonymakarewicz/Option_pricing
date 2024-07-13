//
// Created by anthony on 18/02/2024.
//

#ifndef OPTION_PRICER_PAYOFF_H
#define OPTION_PRICER_PAYOFF_H

#include <algorithm>
#include <stdexcept>
#include <memory>

class Payoff {
public:
    Payoff(); // Default (no parameter) constructor
    virtual ~Payoff(); // Virtual destructor

    // Method that returns a cloned Payoff* (c.f. copy constructor of Option class)
    [[nodiscard]] virtual std::unique_ptr<Payoff> clone() const = 0;

    // Overloaded operator() which turns the Payoff into an abstract functor
    virtual double operator()(const double& S) const = 0;

    [[nodiscard]] virtual double getK() const = 0;

};

class PayoffCall : public Payoff {
private:
    double K;

public:
    explicit PayoffCall(const double& _K); // Explicit constructor to avoid implicit conversion
    virtual ~PayoffCall();

    std::unique_ptr<Payoff> clone() const override;

    double operator()(const double& S) const override;
};

class PayoffPut : public Payoff {
private:
    double K;

public:
    explicit PayoffPut(const double& _K); // Explicit parameter constructor
    virtual ~PayoffPut();

    std::unique_ptr<Payoff> clone() const override;

    // Overridden operator ()
    double operator()(const double& S) const override;
};


class PayoffDigitalCall : public Payoff {
private:
    double K;

public:
    explicit PayoffDigitalCall(const double& _K);
    virtual ~PayoffDigitalCall();

    std::unique_ptr<Payoff> clone() const override;

    double operator()(const double& S) const override;
};


class PayoffDigitalPut : public Payoff {
private:
    double K;

public:
    explicit PayoffDigitalPut(const double& _K); // Explicit parameter constructor
    virtual ~PayoffDigitalPut();

    std::unique_ptr<Payoff> clone() const override;

    // Overridden operator ()
    double operator()(const double& S) const override;
};

// DoubleDigital options are both call and put
class PayoffDoubleDigital : public Payoff {
private:
    double K_L;
    double K_U;

public:
    explicit PayoffDoubleDigital(const double& _K_L, const double& _K_U);
    virtual ~PayoffDoubleDigital();

    std::unique_ptr<Payoff> clone() const override;

    double operator()(const double& S) const override;
};








#endif //OPTION_PRICER_PAYOFF_H
