#ifndef OPTION_PRICER_OPTION_H
#define OPTION_PRICER_OPTION_H

#include <memory>
#include <string>
#include "payoff.h"
#include "market_data.h"

// Option asbtract base class where *this must be managed by a shared_ptr
class Option : public MarketDataObserver, public std::enable_shared_from_this<Option> {
public:
    /** @brief Option base class
     *
     * This asbtract base class serves as an interface shared by all particular types of options.
     * In addition, this class inherits from the simple MarketDataObserver asbtract class
     * that enforce all subclasses to implement the update method when market data changes.
     *
     * This class does not store directly the StockData object which is only managed by the MarketData
     * singleton object, but it accesses it through the MarketData object.
     *
     * In addition, the Option has a Payoff function object (aka functor) that handles the computation
     * of the payoff for particualr types of Options. Being a funcotr, it also stores the strike K
     * used to compute the payoff.
     *
     * This design choice of separating the StockData and the Payoff objects from the Option class
     * follows the composition over inheritance principle
     *
     * Note: Instances of derived classes must be managed by a std::shared_ptr.and is handled
     * by the factory method associated wiht the particular option type.
     *
     **/
    // Constructors
    Option(const Option& other); // Copy constructor
    Option(Option&& other) noexcept; // Move constructor

    // Destructor
    ~Option() override;

    // Assignment operators
    Option& operator=(const Option& other); // Copy assignment operator
    Option& operator=(Option&& other) noexcept; // Move assignment operator

    void update() override; // Update method called when MarketData changes
    friend std::ostream& operator<<(std::ostream& os, const Option& option); // External overload
    virtual double calc_price() const = 0; // Force all subclasses to deifne this method

    void initialize() {
        marketData_->addObserver(shared_from_this()); // Implicit casting from Option to MarketDataObserver
    }

protected:
    Option(std::string ticker, std::unique_ptr<Payoff>&& payoff, const double& T); // Parameter constructor

    // Utility functions for the copy & move semantics
    void copyFrom(const Option& other);
    void moveFrom(Option&& other);

    double T_; // Maturity of the Option
    std::unique_ptr<Payoff> payoff_; // Unique ptr to Payoff functor
    std::shared_ptr<MarketData> marketData_; // Shared ptr to MarketData singleton
};


// Factory asbtract interface for Option
class OptionFactory {
public:
    virtual ~OptionFactory() = default;
    // Factory method to create specific Option instances
    virtual std::shared_ptr<Option> createOption(std::string ticker,
                                                 std::unique_ptr<Payoff>&& payoff,
                                                 const double& T) = 0;
};

// Concrete class declared as final for devirtualization
class VanillaOption final : public Option {
public:
    ~VanillaOption() override = default;
    double calc_price() const override;// Implementation of the pure virtual method

protected:
    // Protected parameterized constructor to enforce creation through factory method
    VanillaOption(std::string ticker, std::unique_ptr<Payoff>&& payoff, const double& T);
    friend class VanillaOptionFactory;
};


class VanillaOptionFactory final : public OptionFactory {
public:
    std::shared_ptr<Option> createOption(std::string ticker,
                                         std::unique_ptr<Payoff>&& payoff,
                                         const double& T) override {
        if (!dynamic_cast<PayoffSingleStrike*>(payoff.get())) {
            throw std::invalid_argument("VanillaOption only supports PayoffSingleStrike derived classes");
        }
        auto option =  std::shared_ptr<Option>(new VanillaOption(std::move(ticker), std::move(payoff), T));
        option->initialize();
        return option;
    }
};



/*
class EuropeanOption : public VanillaOption {
public:
    EuropeanOption(const std::string& ticker, std::unique_ptr<Payoff>&& payoff, const double& T);
    ~EuropeanOption() override = default;
    double calc_price() const override;
};


class AmericanOption : public VanillaOption {
public:
    AmericanOption(const std::string& ticker, std::unique_ptr<Payoff>&& payoff, const double& T);
    ~AmericanOption() override = default;
    double calc_price() const override;
};

*/

#endif //OPTION_PRICER_OPTION_H
