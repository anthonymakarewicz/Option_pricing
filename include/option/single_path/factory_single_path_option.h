#ifndef FACTORY_SINGLE_PATH_OPTION_H
#define FACTORY_SINGLE_PATH_OPTION_H

#include "option/single_path/base_single_path_option.h"
#include "option/factory_option.h"
#include "option/parameter_object.h"

namespace OptionPricer {
    class SinglePathOptionFactory : public OptionFactory {
    public:
        [[nodiscard]] std::shared_ptr<SinglePathOption> createCallOption(const ParameterObject& params);

        [[nodiscard]] std::shared_ptr<SinglePathOption> createPutOption(const ParameterObject& params);

    protected:
        virtual std::shared_ptr<SinglePathOption> createOption(const ParameterObject& params, const std::string& type) = 0;
    };
}

#endif //FACTORY_SINGLE_PATH_OPTION_H
