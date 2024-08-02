#ifndef FACTORY_OPTION_H
#define FACTORY_OPTION_H

#include <string>
#include "payoff/base_payoff.h"
#include "option/base_option.h"
#include "option/parameter_object.h"

namespace OptionPricer {
    class OptionFactory {
    public:
        virtual ~OptionFactory();

        // Non-static create methods as we use virtual methods
        [[nodiscard]] std::shared_ptr<Option> createCallOption(const ParameterObject& params);
        [[nodiscard]] std::shared_ptr<Option> createPutOption(const ParameterObject& params);

    protected:
        // Template method pattern
        std::shared_ptr<Option> createOption(const ParameterObject& params, const std::string& type);

        // Can be overiden to add extra parameters
        virtual std::string invalidParams(const std::string& option_type) const;

        // To be overidden in concrete factories
        virtual std::unique_ptr<Payoff> createSpecificPayoff(const ParameterObject& params,
                                                             const std::string& type) = 0;
        virtual std::shared_ptr<Option> createSpecificOption(const ParameterObject& params,
                                                             std::unique_ptr<Payoff> payoff,
                                                             const std::shared_ptr<IMarketData>& marketData) = 0;
        virtual std::string getType(const std::string& type) const = 0;
    };
}

#endif //FACTORY_OPTION_H
