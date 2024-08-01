#ifndef FACTORY_DIGITAL_OPTION_H
#define FACTORY_DIGITAL_OPTION_H

#include "option/single_path/factory_single_path_option.h"

namespace OptionPricer {
    class DigitalOptionFactory final: public SinglePathOptionFactory {
        std::shared_ptr<SinglePathOption> createOption(const ParameterObject& params, const std::string& type) override;
    };
}

#endif //FACTORY_DIGITAL_OPTION_H
