#ifndef BASE_SINGLE_PATH_OPTION_H
#define BASE_SINGLE_PATH_OPTION_H

class SinglePathOption : public Option {
public:
    ~SinglePathOption() override = default;

protected:
    // Protected parameterized constructor to enforce creation through factory method
    SinglePathOption(std::string ticker, std::unique_ptr<Payoff>&& payoff, const double& T);
};

#endif //BASE_SINGLE_PATH_OPTION_H
