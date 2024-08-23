#ifndef MC_ASIAN_H
#define MC_ASIAN_H

#include "solver/monte_carlo/base_mc.h"
#include "option/path_dependent/asian_option.h"

namespace OptionPricer {

    class AsianMCPricer : public MCPricer {
    public:
        AsianMCPricer(std::shared_ptr<AsianOption> option,
                      std::shared_ptr<IMarketData> marketData,
                      std::shared_ptr<StockModel> stockModel);

        [[nodiscard]] double calculatePrice(const unsigned long& N) const override;

    protected:
        virtual double computeSumPrices(const double& S_t) const = 0;
        virtual double computeAveragePrice(const double& averagePrice, const unsigned int &steps) const = 0;

        std::shared_ptr<AsianOption> option_;
    };


    class ArithmeticAsianMCPricer final: public AsianMCPricer {
    public:
        ArithmeticAsianMCPricer(std::shared_ptr<ArithmeticAsianOption> option,
                                std::shared_ptr<IMarketData> marketData,
                                std::shared_ptr<StockModel> stockModel);

    private:
        double computeSumPrices(const double& S_t) const override;
        double computeAveragePrice(const double& averagePrice, const unsigned int &steps) const override;
    };


    class GeometricAsianMCPricer final: public AsianMCPricer {
    public:
        GeometricAsianMCPricer(std::shared_ptr<GeometricAsianOption> option,
                               std::shared_ptr<IMarketData> marketData,
                               std::shared_ptr<StockModel> stockModel);

    private:
        double computeSumPrices(const double& S_t) const override;
        double computeAveragePrice(const double& averagePrice, const unsigned int &steps) const override;
    };

}

#endif //MC_ASIAN_H
