#ifndef DOUBLE_DIGITAL_OPTION_CPP
#define DOUBLE_DIGITAL_OPTION_CPP

#include "../base_single_path_option.h"

class DoubleDigitalOption : public SinglePathOption {
public:
    ~DoubleDigitalOption() override = default;
    [[nodiscard]] double calc_price() const override;

private:
    DoubleDigitalOption(const std::string& ticker, std::unique_ptr<Payoff>&& payoff, const double& T);
    friend class DoubleDigitalOptionFactory;
};

#endif //DOUBLE_DIGITAL_OPTION_CPP
