#ifndef BASE_OPTION_H
#define BASE_OPTION_H

#include <string>
#include "payoff/base_payoff.h"
#include "market_data/interface_market_data.h"

namespace OptionPricer {

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
        // Destructor
        ~Option() override;

        // Forbid copy and move semantics
        Option(const Option& other) = delete; // Copy constructor
        Option(Option&& other) noexcept = delete; // Move constructor
        Option& operator=(const Option& other) = delete;// Copy assignment operator
        Option& operator=(Option&& other) noexcept = delete;// Move assignment operator

        void update() override; // Update method called when MarketData changes
        friend std::ostream& operator<<(std::ostream& os, const Option& option); // External overload
        bool operator==(const Option& other) const;
        bool operator!=(const Option& other) const;
        virtual double calc_price() const = 0; // Force all subclasses to deifne this method

        void initialize();
        std::string getType() const;
        [[nodiscard]] const Payoff& getPayoff() const;
        double getT() const;

        double payoff(const double& S) const;
        double payoff(const double& S, const double& extremeS) const;

    protected:
        Option(const std::string& ticker, std::unique_ptr<Payoff> payoff, const double& T,
            std::shared_ptr<IMarketData> marketData); // Parameter constructor

        double T_; // Maturity of the Option
        std::unique_ptr<Payoff> payoff_; // Unique ptr to Payoff functor
        std::shared_ptr<IMarketData> marketData_; // Shared ptr to IMarketData interface
    };

};

#endif //BASE_OPTION_H
