#include "market_data/stock_data.h"
#include <ostream>

namespace OptionPricer {

    StockData::StockData(const double& S, const double& sigma, const std::optional<double>& c)
    : S_(S), sigma_(sigma), c_(c) {
        validate();
    }

    [[nodiscard]] double StockData::getPrice() const {
        return S_;
    }

    [[nodiscard]] double StockData::getSigma() const {
        return sigma_;
    }

    [[nodiscard]] std::optional<double> StockData::getCoupon() const {
        return c_;
    }

    bool StockData::operator==(const StockData& other) const {
        if (S_ != other.S_ || sigma_ != other.sigma_) {
            return false;
        }
        if (!c_.has_value() != !other.c_.has_value()) {
            return false;
        }
        if (c_.has_value() && other.c_.has_value() && c_.value() != other.c_.value()) {
            return false;
        }
        return true;
    }

    bool StockData::operator!=(const StockData &other) const {
        return !(*this == other);
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
        os << "  -> Price: " << stockData.getPrice() << "\n";
        os << "  -> Volatility: " << stockData.getSigma() << "\n";
        if (stockData.getCoupon().has_value()) {
            os << "  -> Coupon: " << stockData.getCoupon().value() << "\n";
        }
        return os;
    }

}