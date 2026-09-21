#ifndef ARGUMENTS_H
#define ARGUMENTS_H
#include <cstdint>
#include <filesystem>
#include <string>
#include <vector>

struct ProgramOptions {
    std::string summaryName;
    std::filesystem::path inputPath;
    std::filesystem::path outputPath;
    std::uint64_t seed;
    std::vector<std::string> summaryArguments;
};

ProgramOptions parseArguments(int argc, char* argv[]);

#endif
