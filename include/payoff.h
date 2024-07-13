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
    explicit PayoffCall(const double& K); // Explicit constructor to avoid implicit conversion
    ~PayoffCall() override;

    [[nodiscard]] std::unique_ptr<Payoff> clone() const override;
    double operator()(const double& S) const override;

private:
    double K_;
};


class PayoffPut : public Payoff {
public:
    explicit PayoffPut(const double& K); // Explicit parameter constructor
    ~PayoffPut() override;

    [[nodiscard]] std::unique_ptr<Payoff> clone() const override;
    double operator()(const double& S) const override;

private:
    double K_;
};


class PayoffDigitalCall : public Payoff {
public:
    explicit PayoffDigitalCall(const double& K);
    ~PayoffDigitalCall() override;

    [[nodiscard]] std::unique_ptr<Payoff> clone() const override;
    double operator()(const double& S) const override;

private:
    double K_;
};


class PayoffDigitalPut : public Payoff {
public:
    explicit PayoffDigitalPut(const double& K); // Explicit parameter constructor
    ~PayoffDigitalPut() override;

    [[nodiscard]] std::unique_ptr<Payoff> clone() const override;
    double operator()(const double& S) const override;

private:
    double K_;
};

// DoubleDigital options are both call and put
class PayoffDoubleDigital : public Payoff {
public:
    explicit PayoffDoubleDigital(const double& K_L, const double& K_U);
    ~PayoffDoubleDigital() override;

    [[nodiscard]] std::unique_ptr<Payoff> clone() const override;
    double operator()(const double& S) const override;

private:
    double K_L_;
    double K_U_;
};



#endif //OPTION_PRICER_PAYOFF_H
