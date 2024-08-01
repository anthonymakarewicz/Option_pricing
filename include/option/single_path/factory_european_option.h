#ifndef FACTORY_EUROPEAN_OPTION_H
#define FACTORY_EUROPEAN_OPTION_H

#include "option/single_path/factory_single_path_option.h"

namespace OptionPricer {
    class EuropeanOptionFactory final: public SinglePathOptionFactory {
        std::shared_ptr<SinglePathOption> createOption(const ParameterObject& params, const std::string& type) override;
    };
}



#endif //FACTORY_EUROPEAN_OPTION_H
