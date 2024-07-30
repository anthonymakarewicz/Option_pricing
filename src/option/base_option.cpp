#include <iostream>
#include <stdexcept>
#include <typeinfo>
#include <cxxabi.h>
#include "option/base_option.h"

#include <payoff/single_strike/base_payoff_vanilla.h>

/**
* @brief Constructor implementation
*
* First the constrcutor tries to assign the maturity entered by the User.
* If it wokrs, then get teh MarketData if it does exist, if it does not then create it.
* Then, try to access the stockData object based on the ticker symbol entered by the User.
* If it does not exists then getStockData will throw and erro (cf. market_data.cpp)
* After, move the payoff unique_ptr to the payoff_ attribute and add a shared_ptr to the current
* object being created when the constructor is called to the list of observers
**/

namespace OptionPricer {
    Option::Option(const std::string& ticker,
                   std::unique_ptr<Payoff> payoff,
                   const double& T,
                   std::shared_ptr<IMarketData> marketData)
        : MarketDataObserver(ticker), T_(T), marketData_(std::move(marketData)) {
        if (T < 0) throw std::invalid_argument("Time to expiration (T) must be positive.");
        // Try to retrieve StockData if not found it throws an exception
        auto stockData = marketData_->getStockData(id_);
        payoff_ = std::move(payoff); // Safely move the payoff
    }

    Option::~Option() {
        if (marketData_) marketData_->removeObserver();
        std::cout << getType() << " on " << id_ << " is destroyed!" << "\n";
    }

    void Option::update() {
        std::cout << "StockData " << id_ << " updated!" << "\n";
        std::cout << "The new Option price is: "<< calc_price() << "\n";
    }

    std::ostream& operator<<(std::ostream& os, const Option& option) {
        if (!option.marketData_) {
            throw std::runtime_error("MarketData object is missing");
        }
        os << "Option:\n"; // Use of "\n" instead of std::endl to avoid flusing the buffer
        os << "  -> Type: " << option.getType() << "\n";
        os << "  -> Expiration: " << option.T_ << " year" << "\n";
        if (option.payoff_) {
            os << "Payoff:\n";
            os << *option.payoff_;
        } else {
            throw std::runtime_error("Payoff object is missing");
        }
        const auto stockData = option.marketData_->getStockData(option.id_);
        os << "Stock:\n";
        os << "  -> Ticker: " << option.id_ << "\n";
        os << *stockData;
        os << "MarketData:\n";
        os << "  -> Risk Free Interest Rate: " << option.marketData_->getR() << "\n";
        return os;
    }

    void Option::initialize() {
        marketData_->addObserver(shared_from_this()); // Implicit casting from Option to MarketDataObserver
    }

    std::string Option::getType() const {
        // Get the demangled name of the type
        int status;
        const char* mangledName = typeid(*this).name();
        char* demangledName = abi::__cxa_demangle(mangledName, nullptr, nullptr, &status);
        std::string typeName = (status == 0) ? demangledName : mangledName;
        std::free(demangledName);
        return typeName;
    }

    double Option::payoff(const double &S) const {
        return (*payoff_)(S);
    }
}
