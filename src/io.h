#ifndef IO_H
#define IO_H
#include "runner.h"
#include <filesystem>
#include <optional>
#include <vector>

std::vector<Key> loadInput(const std::filesystem::path& path);

void writeOutput(
    const std::vector<Estimate>& estimates,
    const std::optional<std::vector<Estimate>>& topK,
    const std::filesystem::path& path
);

void printStatistics(const RunResult& result);

#endif