#include "io.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <format>

namespace Exceptions {
    constexpr char UNABLE_TO_OPEN_INPUT_FILE[] = "Unable to open input file: {}";
    constexpr char UNABLE_TO_OPEN_OUTPUT_FILE[] = "Unable to open output file: {}";
}

namespace Format {
    constexpr char ESTIMATES_OUTPUT[] = "{} {}\n";
    constexpr char STATISTICS_OUTPUT[] = "UpdateTimeNS: {}\nQueryTimeNS: {}\nMemory: {}\n";
}

std::vector<Key> loadInput(const std::filesystem::path& path) {
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error(std::format(Exceptions::UNABLE_TO_OPEN_INPUT_FILE[], path.string()));
    }
    std::vector<Key> input;
    Key key;
    while (file >> key) {
        input.push_back(key);
    }
    return input;
}

void writeEstimates(const std::vector<Estimate>& estimates, const std::filesystem::path& path) {
    std::ofstream file(path);
    if (!file) {
        throw std::runtime_error(std::format(Exceptions::UNABLE_TO_OPEN_OUTPUT_FILE[], path.string()));
    }

    for (const auto& estimate : estimates) {
        file << std::format(Format::ESTIMATES_OUTPUT, estimate.key, estimate.estimate);
    }
}

void printStatistics(const RunResult& result) {
    std::cout << std::format(Format::STATISTICS_OUTPUT, result.updateTime.count(), result.queryTime.count(), result.memoryUsage); 
}
