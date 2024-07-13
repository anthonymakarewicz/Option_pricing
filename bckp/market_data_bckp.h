//
// Created by anthony on 24/02/2024.
//

#ifndef OPTION_PRICER_MARKET_DATA_H
#define OPTION_PRICER_MARKET_DATA_H

#include <unordered_map>
#include <string>
#include <memory>
#include <vector>
#include <stdexcept>
#include <optional>
#include <mutex>


class StockData {
public:
    StockData(const  double& S, const double& sigma, const std::optional<double>& c = std::nullopt)
        : S_(S), sigma_(sigma), c_(c) {
        validate();
    }

    [[nodiscard]] double getPrice() const { return S_; }
    [[nodiscard]] double getsigma() const { return sigma_; }
    [[nodiscard]] std::optional<double> getCoupon() const { return c_; }

private:
    void setPrice(const double& S) {
        S_ = S;
        validate();
    }

    void setSigma(const double& sigma) {
        sigma_ = sigma;
        validate();
    }

    void setCoupon(const std::optional<double>& c) {
        c_ = c;
        validate();
    }

    void validate() const {
        if (S_ <= 0) {
            throw std::invalid_argument("Price must be positive.");
        }
        if (sigma_ < 0) {
            throw std::invalid_argument("sigma cannot be negative.");
        }
        if (c_.has_value() && (c_.value() < 0 | c_.value() > 1)) {
            throw std::invalid_argument("Coupon rate must be between 0 and 1.");
        }
    }

    double S_;
    double sigma_;
    std::optional<double> c_;

    // Only MarketData is allowed to access private setters
    friend class MarketData;
};


// Observer Interface
class MarketDataObserver {
public:
    virtual ~MarketDataObserver() = default;
    virtual void update() = 0;
};


// Singleton Class
class MarketData {
public:
    static std::shared_ptr<MarketData> getInstance() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
            instance_ = std::make_shared<MarketData>();
        }
        return instance_;
    }

    void addObserver(const std::shared_ptr<MarketDataObserver>& observer) {
        observers_.push_back(observer);
    }
    void removeObserver(const std::shared_ptr<MarketDataObserver>& observer) {
        // Erase_if introduced in C++20
        std::erase_if(observers_, [&observer](const std::weak_ptr<MarketDataObserver>& obs) {
            return obs.lock() == observer;
        });


        /* Erase-remove idiom which was used in former versions of C++
        observers_.erase(std::remove_if(observers_.begin(), observers_.end(),
            [&observer](const std::weak_ptr<MarketDataObserver>& obs) {
                return obs.lock() == observer;
            }), observers_.end());
            */
    }

    void notifyObservers() const {
        for (const auto& observer : observers_) {
            if (auto obs = observer.lock()) {
                obs->update();
            }
        }
    }

    // Perfect forwarding for handling optional dividend rate
    template<typename... Args>
    void addStock(const std::string& ticker, Args&&... args) {
        stockDataMap_[ticker] = std::make_shared<StockData>(std::forward<Args>(args)...);
    }

    // Update the stock through the MarketData
    void updateStockPrice(const std::string& ticker, double S) {
        if (auto it = stockDataMap_.find(ticker); it != stockDataMap_.end()) {
            it->second->setPrice(S);
            notifyObservers();
        }
    }

    void updateStockSigma(const std::string& ticker, double sigma) {
        if (auto it = stockDataMap_.find(ticker); it != stockDataMap_.end()) {
            it->second->setSigma(sigma);
            notifyObservers();
        }
    }

    void updateStockCoupon(const std::string& ticker, std::optional<double> c) {
        if (auto it = stockDataMap_.find(ticker); it != stockDataMap_.end()) {
            it->second->setCoupon(c);
            notifyObservers();
        }
    }

    [[nodiscard]] std::shared_ptr<StockData> getStockData(const std::string& ticker) const {
        if (auto it = stockDataMap_.find(ticker); it != stockDataMap_.end()) {
            return it->second;
        }
        throw std::invalid_argument("Stock data not found for ticker: " + ticker);
    }

    [[nodiscard]] double getR() const { return r_; }
    void setR(double r) {
        r_ = r;
        notifyObservers();
    }

private:
    MarketData() : r_(0.05) {}; // Private constructor with default IR of 5%

    static std::shared_ptr<MarketData> instance_;
    static std::mutex mutex_;

    double r_;
    std::unordered_map<std::string, std::shared_ptr<StockData>> stockDataMap_;
    std::vector<std::weak_ptr<MarketDataObserver>> observers_;
};

// Initialize the static members
std::shared_ptr<MarketData> MarketData::instance_ = nullptr;
std::mutex MarketData::mutex_;


#endif //OPTION_PRICER_MARKET_DATA_H
