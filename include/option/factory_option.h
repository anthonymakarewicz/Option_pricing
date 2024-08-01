#ifndef FACTORY_OPTION_H
#define FACTORY_OPTION_H

#include <string>

namespace OptionPricer {
    class OptionFactory {
    public:
        virtual ~OptionFactory() = 0;

    protected:
        [[nodiscard]] virtual std::string invalidParams(const std::string& option_type) const;
    };

    inline OptionFactory::~OptionFactory() = default;
}

#endif //FACTORY_OPTION_H
