#include "market_data/market_data_observer.h"

namespace OptionPricer {
    MarketDataObserver::MarketDataObserver(const std::string &id) : id_(id) {}

    MarketDataObserver::~MarketDataObserver() = default;

    std::string MarketDataObserver::getID() const {
        return id_;
    }
}