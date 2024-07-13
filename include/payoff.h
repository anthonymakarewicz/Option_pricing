#ifndef OPTION_PRICER_PAYOFF_H
#define OPTION_PRICER_PAYOFF_H

#include <algorithm>
#include <memory>


class Payoff {
public:
    Payoff(); // Default (no parameter) constructor
    virtual ~Payoff(); // Virtual destructor

    [[nodiscard]] virtual double getK() const = 0;

    // Method that returns a cloned Payoff* (c.f. copy constructor of Option class)
    [[nodiscard]] virtual std::unique_ptr<Payoff> clone() const = 0;

    // Overloaded operator() which turns the Payoff into an abstract functor
    virtual double operator()(const double& S) const = 0;


};


class PayoffCall : public Payoff {
public:
    explicit PayoffCall(const double& _K); // Explicit constructor to avoid implicit conversion
    virtual ~PayoffCall();

    std::unique_ptr<Payoff> clone() const override;
    double operator()(const double& S) const override;

private:
    double K;
};


class PayoffPut : public Payoff {
public:
    explicit PayoffPut(const double& _K); // Explicit parameter constructor
    virtual ~PayoffPut();

    std::unique_ptr<Payoff> clone() const override;
    double operator()(const double& S) const override;

private:
    double K;
};


class PayoffDigitalCall : public Payoff {
public:
    explicit PayoffDigitalCall(const double& _K);
    virtual ~PayoffDigitalCall();

    std::unique_ptr<Payoff> clone() const override;
    double operator()(const double& S) const override;

private:
    double K;
};


class PayoffDigitalPut : public Payoff {
public:
    explicit PayoffDigitalPut(const double& _K); // Explicit parameter constructor
    virtual ~PayoffDigitalPut();

    std::unique_ptr<Payoff> clone() const override;
    double operator()(const double& S) const override;

private:
    double K;
};

// DoubleDigital options are both call and put
class PayoffDoubleDigital : public Payoff {
public:
    explicit PayoffDoubleDigital(const double& _K_L, const double& _K_U);
    virtual ~PayoffDoubleDigital();

    std::unique_ptr<Payoff> clone() const override;
    double operator()(const double& S) const override;

private:
    double K_L;
    double K_U;
};



#endif //OPTION_PRICER_PAYOFF_H
