#ifndef DIGITAL_OPTION_H
#define DIGITAL_OPTION_H

#include "../base_single_path_option.h"

class DigitalOption final : public SinglePathOption {
public:
    ~DigitalOption() override = default;
    [[nodiscard]] double calc_price() const override;

private:
    DigitalOption(const std::string& ticker, std::unique_ptr<Payoff>&& payoff, const double& T);
    friend class DigitalOptionFactory;
};

#endif //DIGITAL_OPTION_H
