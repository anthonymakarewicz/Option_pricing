#ifndef OPTION_PRICER_OPTION_H
#define OPTION_PRICER_OPTION_H

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

    void initialize();
    [[nodiscard]] std::string getType() const;

protected:
    Option(std::string ticker, std::unique_ptr<Payoff>&& payoff, const double& T); // Parameter constructor

    // Utility functions for the copy & move semantics
    void copyFrom(const Option& other);
    void moveFrom(Option&& other);

    double T_; // Maturity of the Option
    std::unique_ptr<Payoff> payoff_; // Unique ptr to Payoff functor
    std::shared_ptr<MarketData> marketData_; // Shared ptr to MarketData singleton
};


// Concrete class declared as final for devirtualization
class SinglePathOption : public Option {
public:
    ~SinglePathOption() override = default;
    double calc_price() const override;// Implementation of the pure virtual method

protected:
    // Protected parameterized constructor to enforce creation through factory method
    SinglePathOption(std::string ticker, std::unique_ptr<Payoff>&& payoff, const double& T);
};


class PathDependentOption : public Option {
public:
    ~PathDependentOption() override = default;

protected:
    // Protected parameterized constructor to enforce creation through factory method
    PathDependentOption(std::string ticker, std::unique_ptr<Payoff>&& payoff, const double& T);
};

// Factory asbtract interface for Option
class OptionFactory {
public:
    virtual ~OptionFactory() = 0;

protected:
    // Can be overidden in subclasses to accomodate extra parameters
    [[nodiscard]] virtual std::string invalidParams(const std::string& option_type) const {
        return "Invalid parameters for " + option_type + "\n"
        "Expected parameters:\n"
        "  - \"ticker\" (string) for ticker symbol\n"
        "  - \"T\" (double) for maturity\n"
        "  - \"K\" (double) for strike\n";
    }
};

inline OptionFactory::~OptionFactory() = default;


class SinglePathOptionFactory : public OptionFactory {
public:
    [[nodiscard]] std::shared_ptr<SinglePathOption> createCallOption(const ParameterObject& params) {
        return createOption(params, "call");
    }

    [[nodiscard]] std::shared_ptr<SinglePathOption> createPutOption(const ParameterObject& params) {
        return createOption(params, "put");
    }
protected:
    virtual std::shared_ptr<SinglePathOption> createOption(const ParameterObject& params, const std::string& type) = 0;
};


class EuropeanOptionFactory : public SinglePathOptionFactory {
private:
    std::shared_ptr<Option> createOption(const ParameterObject& params, const std::string& type) override {
        std::string ticker;
        double T;
        double K;

        // Catch the exception early to inform about the constructor's signature
        try {
            ticker = params.getProperty<std::string>("ticker");
            T = params.getProperty<double>("T");
            K = params.getProperty<double>("K");
        } catch (const std::invalid_argument& e) {
            std::cerr << e.what() << "\n";
            std::cout << invalidParams("European Option");
            throw;
        }

        std::unique_ptr<Payoff> payoff;
        if (type == "call") {
            payoff = std::make_unique<PayoffCall>(K);
        } else if (type == "put") {
            payoff = std::make_unique<PayoffPut>(K);
        } else {
            throw std::invalid_argument("Invalid option type: " + type);
        }

        auto option = std::shared_ptr<SinglePathOption>(new EuropeanOption(ticker, std::move(payoff), T));
        option->initialize();
        return option;
    }
};


class EuropeanOption : public SinglePathOption {
public:
    ~EuropeanOption() override = default;
    [[nodiscard]] double calc_price() const override;

private:
    EuropeanOption(const std::string& ticker, std::unique_ptr<Payoff>&& payoff, const double& T);
    friend class EuropeanOptionFactory;
};



std::shared_ptr<Option> createOption(const PropertySet& params) const {
        std::string ticker;
        double T;
        double strike;

        try {
            ticker = params.getProperty<std::string>("ticker");
            T = params.getProperty<double>("T");
            strike = params.getProperty<double>("strike");
        } catch (const std::exception& e) {
            invalidParams();
            throw;
        }

        std::string type = params.getProperty<std::string>("type");
        std::unique_ptr<Payoff> payoff;
        if (type == "call") {
            payoff = std::make_unique<PayoffCall>(strike);
        } else if (type == "put") {
            payoff = std::make_unique<PayoffPut>(strike);
        } else {
            throw std::invalid_argument("Invalid option type: " + type);
        }

        auto option = std::make_shared<EuropeanOption>(ticker, std::move(payoff), T);
        option->initialize();
        return option;
    }

    void invalidParams() const {
        std::cerr << "Invalid parameters for European Option\n";
        std::cerr << "Expected parameters:\n";
        std::cerr << "  - ticker (string)\n";
        std::cerr << "  - T (double) for maturity\n";
        std::cerr << "  - strike (double)\n";
    }

class PathDependentOptionFactory : public OptionFactory {
public:
    [[nodiscard]] virtual std::shared_ptr<PathDependentOptionFactory> createCallOption(const PropertySet& propertySet) = 0;
    [[nodiscard]] virtual std::shared_ptr<PathDependentOptionFactory> createPutOption(const PropertySet& propertySetT) = 0;
};


class VanillaOptionFactory final : public OptionFactory {
public:
    /**
     * @brief VanillaOptionFactory
     * Because of the protected constructor of VanillaOption, we cannot directly create the shared_ptr
     * using make_shared. Thus we have to use shared_ptr<>(new ...) which can lead to memeory leak
     * if an exception fails during the creation and/or call of the initialize method. Therefore,
     * we have to create a temporary VanillaOption* to catch an exception that can occur and being
     * able to free the memory if an exception does occur thus preventing memory leakd evne though the use
     * of shared_ptr<>(new ...) is not memory efficient comapred to make_shared<>().
     */
    std::shared_ptr<Option> createOption(std::string ticker,
                                         std::unique_ptr<Payoff>&& payoff,
                                         const double& T) override {
        if (!dynamic_cast<PayoffSingleStrike*>(payoff.get())) {
            throw std::invalid_argument("VanillaOption only supports PayoffSingleStrike derived classes");
        }
        auto optionPtr = std::shared_ptr<Option>(new SinglePathOption(ticker, std::move(payoff), T));
        optionPtr->initialize();
        return optionPtr;
    }
};


class EuropeanOption : public SinglePathOption {
public:
    ~EuropeanOption() override = default;
    [[nodiscard]] double calc_price() const override;

private:
    EuropeanOption(const std::string& ticker, std::unique_ptr<Payoff>&& payoff, const double& T);
    friend class EuropeanOptionFactory;
};

/*
class AmericanOption : public VanillaOption {
public:
    AmericanOption(const std::string& ticker, std::unique_ptr<Payoff>&& payoff, const double& T);
    ~AmericanOption() override = default;
    double calc_price() const override;
};

*/




#endif //OPTION_PRICER_OPTION_H
