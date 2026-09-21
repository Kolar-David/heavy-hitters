#ifndef IO_H
#define IO_H
#include "runner.h"
#include <filesystem>
#include <vector>

std::vector<Key> loadInput(const std::filesystem::path& path);

void writeEstimates(const std::vector<Estimate>& estimates, const std::filesystem::path& path);

void printStatistics(const RunResult& result);

#endif
