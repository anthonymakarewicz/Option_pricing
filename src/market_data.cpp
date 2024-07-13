#ifndef OPTION_PRICER_MARKET_DATA_CPP
#define OPTION_PRICER_MARKET_DATA_CPP

#include <ostream>
#include "market_data.h"
#include "option.h"

// Static member initialization
std::shared_ptr<MarketData> MarketData::instance_ = nullptr;
std::mutex MarketData::mutex_;

// StockData implementation
StockData::StockData(const double& S, const double& sigma, const std::optional<double>& c)
    : S_(S), sigma_(sigma), c_(c) {
    validate();
}

// Prefix common guetters with nodiscard C++17
[[nodiscard]] double StockData::getPrice() const {
    return S_;
}

[[nodiscard]] double StockData::getSigma() const {
    return sigma_;
}

[[nodiscard]] std::optional<double> StockData::getCoupon() const {
    return c_;
}

void StockData::setPrice(const double& S) {
    S_ = S;
    validate();
}

void StockData::setSigma(const double& sigma) {
    sigma_ = sigma;
    validate();
}

void StockData::setCoupon(const std::optional<double>& c) {
    c_ = c;
    validate();
}

void StockData::validate() const {
    if (S_ <= 0) {
        throw std::invalid_argument("Price must be positive.");
    }
    if (sigma_ < 0) {
        throw std::invalid_argument("Sigma cannot be negative.");
    }
    // Check if the optional dividend was specified before accessing
    if (c_.has_value() && (c_.value() < 0 || c_.value() > 1)) {
        throw std::invalid_argument("Coupon rate must be between 0 and 1.");
    }
}

std::ostream& operator<<(std::ostream& os, const StockData& stockData) {
    os << "Price: " << stockData.getPrice()
       << ", Volatility: " << stockData.getSigma();
    if (stockData.getCoupon().has_value()) {
        os << ", Coupon: " << stockData.getCoupon().value();
    }
    return os;
}

// MarketData implementation
std::shared_ptr<MarketData> MarketData::getInstance() {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!instance_) {
        instance_ = std::make_shared<MarketData>();
    }
    return instance_;
}
// Initlize risk-free interest with some default value
MarketData::MarketData() : r_(0.05) {}

void MarketData::addObserver(const std::shared_ptr<MarketDataObserver>& observer) {
    observers_.push_back(observer);
}

void MarketData::removeObserver(const std::shared_ptr<MarketDataObserver>& observer) {
    // Erase_if introduced in C++20 that replace the erase-remove idiom
    std::erase_if(observers_, [&observer](const std::weak_ptr<MarketDataObserver>& obs) {
        return obs.lock() == observer;
    });
}

/**
 * @brief This method will notify only specific observers with ticker
 * as ticker symbol. First, this function checks wether the weak_ptr can access
 * the shared_ptr of MarketData observer it observes. If obs actually poiints to an existing
 * shared_ptr, then it safely casts the shared_ptr<MarketData> as a shared_ptr<Option> before
 * checking wether its ticker matches the one speicified as paramter.
 *
 * As the MarketData class serves only an interface that the Option class must implement
 * and it has no other subclasses, then it is reasonable to assume that the casting will
 * succeed. In fact, the observers_ being a std::vector<std::weak_ptr<MarketDataObserver>>
 * and as MarketDataObserver is an asbtarct class, at run time observers_ will actually
 * poin to Option objects.
 *
 */
void MarketData::notifyObserver(const std::string& ticker) const {
    for (const auto& observer : observers_) {
        if (auto obs = observer.lock()) {
            if (auto opt = std::dynamic_pointer_cast<Option>(obs)) {
                if (opt->getTicker() == ticker) {
                    opt->update();
                }
            }
        }
    }
}

// Overloaded method that notify all observers
void MarketData::notifyObservers() const {
    for (const auto& observer : observers_) {
        if (auto obs = observer.lock()) {
            obs->update();
        }
    }
}

void MarketData::updateStockPrice(const std::string& ticker, double S) {
    // If statement with initializer C++17
    if (auto it = stockDataMap_.find(ticker); it != stockDataMap_.end()) {
        it->second->setPrice(S);
        notifyObserver(ticker);
    } else {
        throw std::invalid_argument(ticker + ' is no present in the MarketData object');
    }
}

void MarketData::updateStockSigma(const std::string& ticker, double sigma) {
    if (auto it = stockDataMap_.find(ticker); it != stockDataMap_.end()) {
        it->second->setSigma(sigma);
        notifyObserver(ticker);
    } else {
        throw std::invalid_argument(ticker + ' is no present in the MarketData object');
    }
}

void MarketData::updateStockCoupon(const std::string& ticker, std::optional<double> c) {
    if (auto it = stockDataMap_.find(ticker); it != stockDataMap_.end()) {
        it->second->setCoupon(c);
        notifyObserver(ticker);
    } else {
        throw std::invalid_argument(ticker + ' is no present in the MarketData object');
    }
}

std::shared_ptr<StockData> MarketData::getStockData(const std::string& ticker) const {
    if (auto it = stockDataMap_.find(ticker); it != stockDataMap_.end()) {
        return it->second;
    }
    throw std::invalid_argument("Stock data not found for ticker: " + ticker);
}

[[nodiscard]] double MarketData::getR() const {
    return r_;
}

void MarketData::setR(const double& r) {
    r_ = r;
    notifyObservers();
}


#endif //OPTION_PRICER_MARKET_DATA_CPP