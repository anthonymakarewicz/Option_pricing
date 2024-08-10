#ifndef GENERATOR_H
#define GENERATOR_H

#include <random>
#include <cmath>
#include <limits>
#include <iostream>
#include <boost/random/faure.hpp>
#include <boost/random/sobol.hpp>

namespace OptionPricer {
    class Distribution {
    public:
        virtual ~Distribution() = default;
        [[nodiscard]] virtual double inv_cdf(const double& quantile) const = 0;
        virtual double operator()(std::mt19937& gen) = 0;
    };

    class StandardNormalDistribution : public Distribution {
    public:
        explicit StandardNormalDistribution()
            : normal_dist_(0.0, 1.0) {}

        [[nodiscard]] double inv_cdf(const double& quantile) const override {
            /* This function implements the Beasley-Springer-Moro (BSM) algorithm
             * for approximating the inverse cumulative distribution function (CDF)
             * of the standard normal distribution, as described in Glasserman [2004].
             */

            if (quantile <= 0.0 || quantile >= 1.0) {
                throw std::invalid_argument("quantile must be between (0,1)");
            }

            const bool sup = quantile > 0.5;
            const double up = sup ? 1.0 - quantile : quantile;

            // Coefficients for the rational approximation of the central region
            static constexpr double a0 = 2.50662823884;
            static constexpr double a1 = -18.61500062529;
            static constexpr double a2 = 41.39119773534;
            static constexpr double a3 = -25.44106049637;

            static constexpr double b0 = -8.47351093090;
            static constexpr double b1 = 23.08336743743;
            static constexpr double b2 = -21.06224101826;
            static constexpr double b3 = 3.13082909833;

            // Coefficients for the polynomial approximation of the tail region
            static constexpr double c0 = 0.3374754822726147;
            static constexpr double c1 = 0.9761690190917186;
            static constexpr double c2 = 0.1607979714918209;
            static constexpr double c3 = 0.0276438810333863;
            static constexpr double c4 = 0.0038405729373609;
            static constexpr double c5 = 0.0003951896511919;
            static constexpr double c6 = 0.0000321767881768;
            static constexpr double c7 = 0.0000002888167364;
            static constexpr double c8 = 0.0000003960315187;

            double x = up - 0.5;
            double r;

            // Use rational approximation for quantiles in the central right region
            if (fabs(x) < 0.42) {
                r = x*x;
                r = x * (((a3*r + a2)*r + a1)*r + a0) / ((((b3*r + b2)*r + b1)*r + b0)*r + 1.0);
                return sup ? -r: r;
            }

            // Use Chebyshev polynomial approximation for quantiles in the right tail
            r = up;
            r = log(-log(r));
            r = c0 + r*(c1 + r*(c2 + r*(c3 + r*(c4 + r*(c5 + r*(c6 + r*(c7 + r*c8)))))));

            // Use symmetry property of the standard normal distribution
            return sup? r: -r;
        }

        double operator()(std::mt19937& gen) override {
            return normal_dist_(gen);
        }

    private:
        std::normal_distribution<> normal_dist_;
    };

    class NumberGenerarator {
    public:
        // Initialize the seed with user specified one
        explicit NumberGenerarator(std::shared_ptr<Distribution> dist, const unsigned int& seed)
        : dist_(std::move(dist)), seed_(seed) {
            if (seed_ < 0) {
                throw std::invalid_argument("seed parameetr must be a positve integer");
            }
        }

        // Initialize the seed using 'true' randomness
        explicit NumberGenerarator(std::shared_ptr<Distribution> dist) : dist_(std::move(dist)) {
            std::random_device rd;
            seed_ = rd();
        }

        virtual ~NumberGenerarator() = default;
        virtual double generate(const int& step) = 0;

    protected:
        std::shared_ptr<Distribution> dist_;
        unsigned int seed_;
    };


    class RNGenerator final: public NumberGenerarator {
    public:
        explicit RNGenerator( std::shared_ptr<Distribution> dist, const unsigned int& seed)
        : NumberGenerarator(std::move(dist), seed), generator_(seed_) {}

        explicit RNGenerator(std::shared_ptr<Distribution> dist)
        : NumberGenerarator(std::move(dist)), generator_(seed_) {}

        [[nodiscard]] double generate(const int& step) override {
            return (*dist_)(generator_);
        }

    private:
        std::mt19937 generator_; // Mersenne Twister PRNG
    };


    class QRNGenerator : public NumberGenerarator {
    public:
        QRNGenerator(std::shared_ptr<Distribution> dist, const unsigned int& seed, const unsigned int& dim)
         : NumberGenerarator(std::move(dist), seed), dim_(dim), point_(dim_) {
            validateDim();
        }

        explicit QRNGenerator(std::shared_ptr<Distribution> dist, const unsigned int& dim)
        : NumberGenerarator(std::move(dist)), dim_(dim), point_(dim_) {
            validateDim();
        }

        ~QRNGenerator() override = default;

        unsigned int getDim() const {
            return dim_;
        }

    protected:
        void validateDim() const {
            if (dim_ < 0) {
                throw std::invalid_argument("dim must be a positive integer");
            }
        }

        unsigned int dim_;
        std::vector<double> point_; // Maybe use array
    };


    class SobolGenerator final: public QRNGenerator {
    public:
        SobolGenerator(std::shared_ptr<Distribution> dist, const unsigned int& seed, const unsigned int& dim)
        : QRNGenerator(std::move(dist),seed, dim), sobolQrng_(dim_) {
            sobolQrng_.seed(seed_);
        }

        explicit SobolGenerator(std::shared_ptr<Distribution> dist, const unsigned int& dim)
        : QRNGenerator(std::move(dist), dim), sobolQrng_(dim_) {
            sobolQrng_.seed(seed_);
        }

        ~SobolGenerator() override = default;

        [[nodiscard]] double generate(const int& step) override {
            if (step == 0) {
                // Generate Sobol sequence point
                sobolQrng_.generate(point_.begin(), point_.end());
            }

            // Normalize and transform using Moro's inversion
            const double uniformValue = point_[step] / static_cast<double>(boost::random::sobol::max());
            return dist_->inv_cdf(uniformValue);
        }

    private:
        boost::random::sobol sobolQrng_;
    };


    class FaureGenerator final: public QRNGenerator {
    public:
        FaureGenerator(std::shared_ptr<Distribution> dist, const unsigned int& seed, const unsigned int& dim)
        : QRNGenerator(std::move(dist), seed, dim), faureQrng_(dim_) {
            faureQrng_.seed(seed_);
        }

        explicit FaureGenerator(std::shared_ptr<Distribution> dist, const unsigned int& dim)
        : QRNGenerator(std::move(dist), dim), faureQrng_(dim_) {
            faureQrng_.seed(seed_);
        }

        ~FaureGenerator() override = default;

        [[nodiscard]] double generate(const int& step) override {
            if (step == 0) {
                // Generate Sobol sequence point
                faureQrng_.generate(point_.begin(), point_.end());
            }

            // Normalize and transform using the inverse CDF
            const double uniform_value = point_[step] / static_cast<double>(boost::random::faure::max());
            return dist_->inv_cdf(uniform_value);
        }

    private:
        boost::random::faure faureQrng_;
    };
}

#endif //GENERATOR_H
