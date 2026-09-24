#include "io.h"
#include <format>
#include <fstream>
#include <iostream>
#include <stdexcept>

namespace Exceptions {
    constexpr char UNABLE_TO_OPEN_INPUT_FILE[] = "Unable to open input file: {}";
    constexpr char UNABLE_TO_OPEN_OUTPUT_FILE[] = "Unable to open output file: {}";
}

namespace Format {
    constexpr char ESTIMATE_OUTPUT[] = "{} {}\n";
    constexpr char ESTIMATES_HEADER[] = "[estimates]\n";
    constexpr char TOP_K_HEADER[] = "\n[top_k]\n";
    constexpr char STATISTICS_OUTPUT[] =
        "UpdateTimeNS: {}\n"
        "QueryTimeNS: {}\n"
        "Memory: {}\n";
}

std::vector<Key> loadInput(const std::filesystem::path& path) {
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error(std::format(Exceptions::UNABLE_TO_OPEN_INPUT_FILE, path.string()));
    }
    std::vector<Key> input;
    Key key;
    while (file >> key) {
        input.push_back(key);
    }
    return input;
}

void writeOutput(const std::vector<Estimate>& estimates, const std::optional<std::vector<Estimate>>& topK, const std::filesystem::path& path) {
    std::ofstream file(path);
    if (!file) {
        throw std::runtime_error(std::format(Exceptions::UNABLE_TO_OPEN_OUTPUT_FILE, path.string()));
    }
    file << Format::ESTIMATES_HEADER;
    for (const auto& estimate : estimates) {
        file << std::format(Format::ESTIMATE_OUTPUT, estimate.key, estimate.estimate);
    }
    if (topK) {
        file << Format::TOP_K_HEADER;
        for (const auto& estimate : *topK) {
            file << std::format(Format::ESTIMATE_OUTPUT, estimate.key, estimate.estimate);
        }
    }
}

void printStatistics(const RunResult& result) {
    std::cout << std::format(Format::STATISTICS_OUTPUT, result.updateTime.count(), result.queryTime.count(), result.memoryUsage);
}