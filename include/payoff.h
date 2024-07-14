#ifndef OPTION_PRICER_PAYOFF_H
#define OPTION_PRICER_PAYOFF_H

#include <algorithm>
#include <memory>


class Payoff {
public:
    Payoff() = default; // Default (no parameter) constructor
    virtual ~Payoff() = default; // Virtual destructor
    [[nodiscard]] virtual std::unique_ptr<Payoff> clone() const = 0;
    // Overloaded operator() which turns the Payoff into an abstract functor
    virtual double operator()(const double& S) const = 0;
};


class PayoffSingleStrike : public Payoff {
public:
    explicit PayoffSingleStrike(const double& K);
    ~PayoffSingleStrike() override = default;

    [[nodiscard]] virtual double getK() const;

protected:
    double K_;
};


class PayoffDoubleStrikes : public Payoff {
public:
    explicit PayoffDoubleStrikes(const double& K_L, const double& K_U);
    ~PayoffDoubleStrikes() override = default;;

    [[nodiscard]] double getKU() const;
    [[nodiscard]] double getKL() const;

protected:
    double K_L_;
    double K_U_;
};

// Define PayoffCall as final for devirtualization of virtual methods
class PayoffCall final : public PayoffSingleStrike {
public:
    explicit PayoffCall(const double& K); // Explicit constructor to avoid implicit conversion
    ~PayoffCall() override = default;
    [[nodiscard]] std::unique_ptr<Payoff> clone() const override;
    double operator()(const double& S) const override;
};

class PayoffPut final : public PayoffSingleStrike {
public:
    explicit PayoffPut(const double& K); // Explicit parameter constructor
    ~PayoffPut() override = default;
    [[nodiscard]] std::unique_ptr<Payoff> clone() const override;
    double operator()(const double& S) const override;
};


class PayoffDigitalCall final : public PayoffSingleStrike {
public:
    explicit PayoffDigitalCall(const double& K);
    ~PayoffDigitalCall() override = default;
    [[nodiscard]] std::unique_ptr<Payoff> clone() const override;
    double operator()(const double& S) const override;
};

class PayoffDigitalPut final : public PayoffSingleStrike {
public:
    explicit PayoffDigitalPut(const double& K); // Explicit parameter constructor
    ~PayoffDigitalPut() override = default;
    [[nodiscard]] std::unique_ptr<Payoff> clone() const override;
    double operator()(const double& S) const override;
};


// DoubleDigital options are both call and put
class PayoffDoubleDigital final : public PayoffDoubleStrikes {
public:
    explicit PayoffDoubleDigital(const double& K_L, const double& K_U);
    ~PayoffDoubleDigital() override = default;
    [[nodiscard]] std::unique_ptr<Payoff> clone() const override;
    double operator()(const double& S) const override;
};



#endif //OPTION_PRICER_PAYOFF_H
