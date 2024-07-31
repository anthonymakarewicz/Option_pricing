#ifndef BASE_OPTION_FACTORY_H
#define BASE_OPTION_FACTORY_H

class OptionFactory {
public:
    virtual ~OptionFactory() = 0;

protected:
    [[nodiscard]] virtual std::string invalidParams(const std::string& option_type) const {
        return "Invalid parameters for " + option_type + "\n"
               "Expected parameters:\n"
               "  - ticker (string) for ticker symbol\n"
               "  - T (double) for maturity\n"
               "  - K (double) for strike\n";
    }
};

inline OptionFactory::~OptionFactory() = default;

#endif //BASE_OPTION_FACTORY_H
