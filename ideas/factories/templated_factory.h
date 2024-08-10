// Base OptionFactory template
template <typename OptionType>
class OptionFactory {
public:
    virtual ~OptionFactory() {}

    // Creates an instance of the specific OptionType
    std::shared_ptr<OptionType> createOption(const ParameterObject& params) {
        auto payoff = createSpecificPayoff(params);
        return createSpecificOption(params, std::move(payoff), marketData_);
    }

protected:
    virtual std::unique_ptr<Payoff> createSpecificPayoff(const ParameterObject& params) = 0;
    virtual std::shared_ptr<OptionType> createSpecificOption(const ParameterObject& params,
                                                             std::unique_ptr<Payoff> payoff,
                                                             const std::shared_ptr<IMarketData>& marketData) = 0;

    std::shared_ptr<IMarketData> marketData_;
};



class AsianOptionFactory : public OptionFactory<AsianOption> {
protected:
    std::unique_ptr<Payoff> createSpecificPayoff(const ParameterObject& params) override {
        // Create a specific payoff for Asian options
        return std::make_unique<Payoff>(); // Use actual Asian payoff creation logic
    }

    std::shared_ptr<AsianOption> createSpecificOption(const ParameterObject& params,
                                                      std::unique_ptr<Payoff> payoff,
                                                      const std::shared_ptr<IMarketData>& marketData) override {
        // Create and return an AsianOption
        return std::make_shared<AsianOption>(); // Add necessary constructor parameters
    }
};


class EuropeanOptionFactory : public OptionFactory<EuropeanOption> {
protected:
    std::unique_ptr<Payoff> createSpecificPayoff(const ParameterObject& params) override {
        // Create a specific payoff for European options
        return std::make_unique<Payoff>(); // Use actual European payoff creation logic
    }

    std::shared_ptr<EuropeanOption> createSpecificOption(const ParameterObject& params,
                                                         std::unique_ptr<Payoff> payoff,
                                                         const std::shared_ptr<IMarketData>& marketData) override {
        // Create and return a EuropeanOption
        return std::make_shared<EuropeanOption>(); // Add necessary constructor parameters
    }
};
