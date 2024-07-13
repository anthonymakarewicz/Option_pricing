//
// Created by anthony on 18/02/2024.
//

#ifndef OPTION_PRICER_OPTION_H
#define OPTION_PRICER_OPTION_H

#include <stdexcept>
#include <ostream>
#include <memory>

#include "payoff.h"

class Option {
protected:
    std::unique_ptr<Payoff> payoff;
    double T;

public:
    Option(std::unique_ptr<Payoff> _payoff,
           const double& _T); // Parameter constructor

    // Virtual destructor for proper memory de-allocation in inheritance
    virtual ~Option();

    // Define deleted copy semantics because of smart pointers
    Option(const Option& other);
    Option& operator=(const Option& rhs);

    // Re-include the default moving constructor and assignment operator
    Option(Option&&) = default;
    Option& operator=(Option&&) = default;

    // Selectors (getters) for our option parameters
    double get_T()     const;

    // Modifiers (setters) for our option parameters
    void set_T(const double& _T);

    // Equality and inequality overloaded operators
    bool operator==(const Option& rhs) const;
    bool operator!=(const Option& rhs) const;

    // Overloaded output stream operator
    friend std::ostream &operator<<(std::ostream& os, const Option& option);

    // Helper method for checking proper moving semantics
    [[nodiscard]] const std::unique_ptr<Payoff>& getPayoff() const {
        return payoff;
    }

    virtual double price() const = 0;
};

#endif //OPTION_PRICER_OPTION_H
