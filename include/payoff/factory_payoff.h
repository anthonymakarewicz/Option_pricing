#ifndef FACTORY_PAYOFF_H
#define FACTORY_PAYOFF_H

#include <string>

namespace OptionPricer {
    class PayoffFactory {
    public:
        virtual ~PayoffFactory() = 0;
    };
    inline PayoffFactory::~PayoffFactory() = default;
}
#endif //FACTORY_PAYOFF_H