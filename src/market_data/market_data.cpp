#include <ostream>
#include <iostream>
#include "market_data/market_data.h"

namespace OptionPricer {

    // Static member initialization to avoid undefined behaviour
    std::shared_ptr<MarketData> MarketData::instance_ = nullptr;
    std::mutex MarketData::mutex_;

    std::shared_ptr<MarketData> MarketData::getInstance() {
        std::lock_guard<std::mutex> lock(mutex_); // Ensure thread safety
        if (!instance_) {
            instance_ = std::shared_ptr<MarketData>(new MarketData());
        }
        return instance_;
    }

    MarketData::~MarketData() = default;

    // Initlize risk-free interest with some default value
    MarketData::MarketData() : r_(0.05) {}

    void MarketData::addObserver(const std::shared_ptr<MarketDataObserver>& observer) {
        observers_.push_back(observer);
    }

    void MarketData::removeObserver() {
        // Erase_if introduced in C++20 that replace the erase-remove idiom
        std::erase_if(observers_, [](const std::weak_ptr<MarketDataObserver>& obs) {
            return obs.expired();
        });
    }

    void MarketData::notifyObserver(const std::string& id) const {
        for (const auto& observer : observers_) {
            if (auto obs = observer.lock()) {
                if (obs->getID() == id) {
                    obs->update();
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
            throw std::invalid_argument(ticker + " is no present in the MarketData object");
        }
    }

    void MarketData::updateStockSigma(const std::string& ticker, double sigma) {
        if (auto it = stockDataMap_.find(ticker); it != stockDataMap_.end()) {
            it->second->setSigma(sigma);
            notifyObserver(ticker);
        } else {
            throw std::invalid_argument(ticker + " is no present in the MarketData object");
        }
    }

    void MarketData::updateStockCoupon(const std::string& ticker, std::optional<double> c) {
        if (auto it = stockDataMap_.find(ticker); it != stockDataMap_.end()) {
            it->second->setCoupon(c);
            notifyObserver(ticker);
        } else {
            throw std::invalid_argument(ticker + " is no present in the MarketData object.");
        }
    }

    std::shared_ptr<const StockData> MarketData::getStockData(const std::string &ticker) const {
        if (auto it = stockDataMap_.find(ticker); it != stockDataMap_.end()) {
            return std::const_pointer_cast<const StockData>(it->second);
        }
        throw std::invalid_argument(ticker + " Stock data not found.");
    }

    double MarketData::getR() const {
        return r_;
    }

    void MarketData::setR(const double& r) {
        r_ = r;
        notifyObservers();
    }

}
