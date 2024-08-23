#ifndef BASE_PAYOFF_H
#define BASE_PAYOFF_H

#include <memory>
#include <string>

namespace OptionPricer {

    enum class PayoffType {
        Call,
        Put,
        DoubleDigital
    };

    inline std::string PayoffTypeToString(const PayoffType& type) {
        switch (type) {
            using enum PayoffType;
            case Call: return "Call";
            case Put: return "Put";
            case DoubleDigital: return "DoubleDigital";
            // Add other cases as needed
            default: return "Unknown";
        }
    }

    // Abstract base class for Payoff
    class Payoff {
    public:
        explicit Payoff(const PayoffType& type);
        virtual ~Payoff();

        PayoffType getPayoffType() const;

        virtual std::string getType() const = 0;
        [[nodiscard]] virtual std::unique_ptr<Payoff> clone() const = 0; // Prototype creational pattern

        virtual void print(std::ostream& os) const;
        friend std::ostream& operator<<(std::ostream& os, const Payoff& payoff);

        bool operator==(const Payoff& other) const;
        bool operator!=(const Payoff& other) const;
        [[nodiscard]] virtual bool compare(const Payoff& other) const = 0;

        // Methods to be overidden in final classes
        virtual double operator()(const double& S) const;
        virtual double operator()(const double& S, const double& extremeS) const;

    protected:
        PayoffType type_;
    };
};

#endif //BASE_PAYOFF_H
