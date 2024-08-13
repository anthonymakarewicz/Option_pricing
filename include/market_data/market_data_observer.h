#ifndef MARKET_DATA_OBSERVER_H
#define MARKET_DATA_OBSERVER_H

#include <string>

namespace OptionPricer {

    class MarketDataObserver {
    public:
        explicit MarketDataObserver(const std::string& id);
        virtual ~MarketDataObserver();

        [[nodiscard]] std::string getID() const;
        virtual void update() = 0;

    protected:
        std::string id_;
    };

}

#endif //MARKET_DATA_OBSERVER_H