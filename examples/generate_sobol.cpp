#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <filesystem>
#include <boost/random/sobol.hpp>


int main() {
    std::filesystem::path path = "";
    
    std::ofstream csvFile("sobol_sequence_5.csv");
    if (!csvFile.is_open()) {
        std::cerr << "Failed to open file for writing." << std::endl;
        return 1;
    }

    boost::random::sobol qrng(2); // 3-dimensional Sobol sequence
    qrng.seed(42);

    std::vector<double> point(2);

    csvFile << "x,y\n";

    std::cout << "Sobol sequence using Boost:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        qrng.generate(point.begin(), point.end());
        for (auto& coord : point)
            coord /= static_cast<double>(boost::random::sobol::max());

        csvFile << std::fixed << std::setprecision(8) << point[0] << "," << point[1] << "\n";
        std::cout << std::endl;
    }
    csvFile.close();

    return 0;
}