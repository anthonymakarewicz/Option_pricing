#ifndef OPTION_PRICER_OPTION_CPP
#define OPTION_PRICER_OPTION_CPP

#include <iostream>
#include <stdexcept>
#include <typeinfo>
#include <cxxabi.h>
#include "option.h"

/* *****************
 * Option base class
 * *****************
*/



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
Option::Option(std::string ticker,
               std::unique_ptr<Payoff>&& payoff,
               const double& T)
    : MarketDataObserver(std::move(ticker)), T_(T) {
    if (T < 0) throw std::invalid_argument("Time to expiration (T) must be positive.");
    // Get the MarketData instance and try to retrieve StockData
    marketData_ = MarketData::getInstance();
    auto stockData = marketData_->getStockData(id_); // If not found it throws an exception

    // Safely move the payoff and pass the observer to MarketData
    payoff_ = std::move(payoff);
}

Option::Option(const Option& other)
    : MarketDataObserver(other.id_),
      std::enable_shared_from_this<Option>(other),
      T_(0.0), payoff_(nullptr), marketData_(nullptr) {
    copyFrom(other);
}

Option::Option(Option&& other) noexcept
    : MarketDataObserver(std::move(other.id_)), T_(0.0), payoff_(nullptr), marketData_(nullptr) {
    moveFrom(std::move(other));
}

Option::~Option() {
    if (marketData_) marketData_->removeObserver();
}

Option& Option::operator=(const Option& other) {
    if (this != &other) {
        copyFrom(other);
    }
    return *this;
}

Option& Option::operator=(Option&& other) noexcept {
    if (this != &other) {
        moveFrom(std::move(other));
    }
    return *this;
}

void Option::update() {
    std::cout << "StockData " << id_ << " updated!" << "\n";
    std::cout << "The new Option price is: "<< calc_price() << "\n";
}

std::ostream& operator<<(std::ostream& os, const Option& option) {
    if (!option.marketData_) {
        throw std::runtime_error("MarketData object is missing");
    }

    // Get the demangled name of the type
    int status;
    const char* mangledName = typeid(option).name();
    char* demangledName = abi::__cxa_demangle(mangledName, nullptr, nullptr, &status);
    std::string typeName = (status == 0) ? demangledName : mangledName;
    std::free(demangledName);
    os << "Type: " << typeName << ", " << "\n"; // Use of "\n" instead of std::endl to avoid flusing the buffer

    os << "Ticker: " << option.id_ << ", Expiration: " << option.T_;
    if (option.payoff_) {
        os << *option.payoff_;
    } else {
        throw std::runtime_error("Payoff object is missing");
    }

    auto stockData = option.marketData_->getStockData(option.id_);
    os << ", StockData: " << *stockData;
    os << ", Risk Free interest rate" << option.marketData_->getR();

    return os;
}

void Option::copyFrom(const Option& other) {
    T_ = other.T_;
    id_ = other.id_;
    if (other.payoff_) {
        payoff_ = other.payoff_->clone(); // Make a deep copy of the Payoff object
    } else {
        throw std::invalid_argument("Payoff object is missing.");
    }
    marketData_ = other.marketData_;
    marketData_->addObserver(shared_from_this()); // Register as an observer
}

void Option::moveFrom(Option&& other) {
    /*
    // Remove the other Option from the observer list if it's registered
    if (other.marketData_) {
        other.marketData_->removeObserver(other.shared_from_this());
    } else {
        throw std::runtime_error("MarketData object missing");
    }
    */
    other.marketData_->removeObserver();
    // Move the attributes from other to *this
    T_ = other.T_;
    id_ = other.id_;
    payoff_ = std::move(other.payoff_);
    marketData_ = std::move(other.marketData_);

    // Ensure the source object is left in a valid state
    other.T_ = 0.0;
    other.id_.clear();
    other.payoff_ = nullptr;
    other.marketData_ = nullptr;

    // Register the current Option as an observer after move
    if (marketData_) {
        marketData_->addObserver(shared_from_this());
    }
}

void Option::initialize() {
    marketData_->addObserver(shared_from_this()); // Implicit casting from Option to MarketDataObserver
}

VanillaOption::VanillaOption(std::string ticker, std::unique_ptr<Payoff>&& payoff, const double& T)
    : Option(std::move(ticker), std::move(payoff), T) {}


double VanillaOption::calc_price() const {
    // Implementation of price calculation for VanillaOption
    return 0.0;
}


#endif //OPTION_PRICER_OPTION_CPP
