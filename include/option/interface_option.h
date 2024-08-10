#ifndef INTERFACE_OPTION_H
#define INTERFACE_OPTION_H

#include "market_data/market_data_observer.h"

namespace OptionPricer {
    class IOption : public MarketDataObserver {
    public:
        explicit IOption(const std::string& id);
        ~IOption() override;

    };
}

#endif //INTERFACE_OPTION_H