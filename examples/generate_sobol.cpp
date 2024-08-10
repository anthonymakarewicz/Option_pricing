#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <boost/random/faure.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/sobol.hpp>
#include <boost/random/uniform_01.hpp>

std::filesystem::path createOutputDir() {
    std::filesystem::path outputDir = "output";
    std::filesystem::path sourceDir = std::filesystem::current_path();
    std::filesystem::path destDir = sourceDir.parent_path().parent_path() / "examples" / outputDir;
    if (!exists(destDir)) {
        create_directory(destDir);
        std::cout << "Directory created: " << destDir << "\n";
    }
    return destDir;
}

int main() {
    unsigned int N = 0, s = 0;
    do {
        std::cout << "Enter the number of samples (N): ";
        std::cin >> N;
        std::cout << "Enter the number of dimensions (s): ";
        std::cin >> s;
    } while (N <= 0 || s <= 0);

    std::string endFileName = boost::lexical_cast<std::string>(s) + ".csv";
    std::filesystem::path csvPath = createOutputDir() / ("sequences_" + endFileName);

    std::ofstream csvFile(csvPath);

    if (!csvFile.is_open()) {
        std::cerr << "Failed to open file for writing." << std::endl;
        return 1;
    }

    unsigned int seed = 42;
    boost::mt19937 unifRng(seed); // Mersenne Twister Pseudo-Random Number Generator (PRNG)
    boost::random::uniform_01<> uniformGen;

    boost::random::sobol sobolQrng(s); // s-dimensional Sobol Quasi Random Number Generator (QRNG)
    boost::random::faure faureQrng(s); // s-dimensional Faure Quasi Random Number Generator (QRNG)

    sobolQrng.seed(seed);
    faureQrng.seed(seed);

    std::vector<double> sobolPoint(s);
    std::vector<double> faurePoint(s);

    // Write header to CSV file
    csvFile << "Sample,Dimension,Sobol,Faure,Uniform\n";

    for (unsigned int i = 1; i <= N; ++i) {
        // Generate Sobol and Faure sequences for this sample
        sobolQrng.generate(sobolPoint.begin(), sobolPoint.end());
        faureQrng.generate(faurePoint.begin(), faurePoint.end());

        for (unsigned int d = 1; d <= s; ++d) {
            // Normalize Sobol and Faure values to [0, 1)
            double sobolVal = sobolPoint[d - 1] / static_cast<double>(boost::random::sobol::max());
            double faureVal = faurePoint[d - 1] / static_cast<double>(boost::random::faure::max());
            double uniformVal = uniformGen(unifRng);

            // Write values to CSV
            csvFile << i << "," << d << ","
                    << std::fixed << std::setprecision(8)
                    << sobolVal << ","
                    << faureVal << ","
                    << uniformVal << "\n";
        }
    }

    csvFile.close();
    std::cout << "Sequences exported to " << csvPath << std::endl;

    return 0;
}
