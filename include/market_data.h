#ifndef OPTION_PRICER_MARKET_DATA_H
#define OPTION_PRICER_MARKET_DATA_H

#include <unordered_map>
#include <string>
#include <utility>
#include <vector>
#include <optional>
#include <mutex>
#include <memory>


// NEED TO PUT STOCKDATA INTO A SPERATE HEADER!

class StockData {
public:
    StockData(const double& S,
              const double& sigma,
              const std::optional<double>& c = std::nullopt);

    // Prefix guetters with nodiscard C++17
    [[nodiscard]] double getPrice() const;
    [[nodiscard]] double getSigma() const;
    [[nodiscard]] std::optional<double> getCoupon() const;
    friend std::ostream& operator<<(std::ostream& os, const StockData& stockData);

private:
    void setPrice(const double& S);
    void setSigma(const double& sigma);
    void setCoupon(const std::optional<double>& c);
    void validate() const;

    double S_; // Stock Price
    double sigma_; // Volatility
    std::optional<double> c_; // Dividen yield as std::optional C++17
    friend class MarketData; // Allow MarketData to access private setters
};


// Declare MarketDataObserver using Observer design pattern
class MarketDataObserver {
public:
    explicit MarketDataObserver(std::string id) : id_(std::move(id)) {}
    virtual ~MarketDataObserver() = default;
    virtual void update() = 0;
    [[nodiscard]] std::string getID() const { return id_; } // More efficient than virtual/final due to vtable usage

protected:
    std::string id_;
};


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
    [[nodiscard]] std::shared_ptr<StockData> getStockData(std::string ticker) const;
    
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

#endif // OPTION_PRICER_MARKET_DATA_H
