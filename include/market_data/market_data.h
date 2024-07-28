#ifndef MARKET_DATA_H
#define MARKET_DATA_H

#include <unordered_map>
#include <string>
#include <utility>
#include <vector>
#include <optional>
#include <mutex>
#include <memory>

#include "stock_data.h"
#include "market_data_observer.h"

// Declare MarketData using Singleton design pattern
class MarketData {
public:
    /** @brief MarketData Singleton class
     *
     * This class serves as a centralized location where all MarketData object will be stored
     * and updated and acces by all MarketDataObserver subclasses instances.
     * Specifically, only 1 instance of the MarketData object will be created when our program
     * will execute be stored as a shared_ptr that all our Options will own the adress of it.
     *
     * This MarketData data will notify all the Option when StockData used for those Options
     * will change.
     *
     */

    // NEED TO ADD DESTRUCTOR!!!

    static std::shared_ptr<MarketData> getInstance();

    ~MarketData();

    // MarketData object should not be clonable
    MarketData(MarketData &other) = delete;
    void operator=(const MarketData &other) = delete;

    // Observer specific methods
    void addObserver(const std::shared_ptr<MarketDataObserver>& observer);
    void removeObserver();
    void notifyObservers() const;
    void notifyObserver(const std::string& id) const; // Notify specific observer

    // Template methods need to be declared inside the header
    template<typename... Args>
    void addStock(const std::string& ticker, Args&&... args) {
        // Perfect forwarding C++17 to preserve rvalue/lvalue ness
        stockDataMap_[ticker] = std::make_shared<StockData>(std::forward<Args>(args)...);
    }

    // Update & access StockData through the MarketData singleton
    void updateStockPrice(const std::string& ticker, double S);
    void updateStockSigma(const std::string& ticker, double sigma);
    void updateStockCoupon(const std::string& ticker, std::optional<double> c);
    [[nodiscard]] std::shared_ptr<StockData> getStockData(const std::string &ticker) const;
    
    [[nodiscard]] double getR() const;
    void setR(const double& r);

private:
    MarketData(); // Declare the constructor as private (common in Singleton pattern)

    static std::shared_ptr<MarketData> instance_;
    static std::mutex mutex_;

    double r_; // Risk-free interest rate
    std::unordered_map<std::string, std::shared_ptr<StockData>> stockDataMap_; // Map ticker symbol to StockData
    std::vector<std::weak_ptr<MarketDataObserver>> observers_; // Use weak_ptr to avoid circular references
};

#endif //MARKET_DATA_H
