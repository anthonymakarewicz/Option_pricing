#ifndef STOCK_DATA_H
#define STOCK_DATA_H

#include <optional>
#include <ostream>

namespace OptionPricer {
    class StockData {
    public:
        StockData(const double& S,
                  const double& sigma,
                  const std::optional<double>& c = std::nullopt);

        [[nodiscard]] double getPrice() const;
        [[nodiscard]] double getSigma() const;
        [[nodiscard]] std::optional<double> getCoupon() const;

        friend std::ostream& operator<<(std::ostream& os, const StockData& stockData);
        bool operator==(const StockData& other) const;
        bool operator!=(const StockData& other) const;

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
}

// Could potentially make the setters public and delete this friendship as getStockData rteurns
// a std::shared_ptr<const StockData> which means that this ptr cannot call non-const methods like setters

#endif //STOCK_DATA_H
