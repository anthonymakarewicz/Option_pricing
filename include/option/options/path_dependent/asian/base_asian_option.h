#ifndef BASE_ASIAN_OPTION_H
#define BASE_ASIAN_OPTION_H

#include "../base_path_dependent_option.h"

class AsianOption: public PathDependentOption {
public:
    ~AsianOption() override;

private:
    AsianOption(const std::string& ticker, std::unique_ptr<Payoff>&& payoff, const double& T);
    friend class PathDependentOptionFactory;
};

#endif //BASE_ASIAN_OPTION_H
