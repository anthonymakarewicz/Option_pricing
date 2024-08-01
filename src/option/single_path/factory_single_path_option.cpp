#include "option/single_path/factory_single_path_option.h"

namespace OptionPricer {
    std::shared_ptr<SinglePathOption> SinglePathOptionFactory::createCallOption(const ParameterObject &params) {
        return createOption(params, "call");
    }

    std::shared_ptr<SinglePathOption> SinglePathOptionFactory::createPutOption(const ParameterObject &params) {
        return createOption(params, "put");
    }
}