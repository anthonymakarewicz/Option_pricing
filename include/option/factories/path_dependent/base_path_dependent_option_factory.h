#ifndef BASE_PATH_DEPENDENT_OPTION_FACTORY_H
#define BASE_PATH_DEPENDENT_OPTION_FACTORY_H

class PathDependentOptionFactory : public OptionFactory {
public:
    [[nodiscard]] std::shared_ptr<PathDependentOptionFactory> createCallOption(const ParameterObject& params) {
        return createOption(params, "call");
    }

    [[nodiscard]] std::shared_ptr<PathDependentOptionFactory> createPutOption(const ParameterObject& params) {
        return createOption(params, "put");
    }

protected:
    virtual std::shared_ptr<PathDependentOptionFactory> createOption(const ParameterObject& params,
         const std::string& type) = 0;
};

#endif //BASE_PATH_DEPENDENT_OPTION_FACTORY_H
