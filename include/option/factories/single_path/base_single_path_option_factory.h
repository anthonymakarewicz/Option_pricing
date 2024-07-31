#ifndef BASE_SINGLE_PATH_OPTION_H
#define BASE_SINGLE_PATH_OPTION_H

class SinglePathOptionFactory : public OptionFactory {
public:
    [[nodiscard]] std::shared_ptr<SinglePathOption> createCallOption(const ParameterObject& params) {
        return createOption(params, "call");
    }

    [[nodiscard]] std::shared_ptr<SinglePathOption> createPutOption(const ParameterObject& params) {
        return createOption(params, "put");
    }

protected:
    virtual std::shared_ptr<SinglePathOption> createOption(const ParameterObject& params, const std::string& type) = 0;


#endif //BASE_SINGLE_PATH_OPTION_H
