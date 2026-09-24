#include "arguments.h"
#include <stdexcept>

constexpr char ERROR_MESSAGE[] =  "Usage: summary-runner <summary> <input> <output> <seed> [summary parameters...] [--top-k]";
constexpr char TOP_K_ARGUMENT[] = "--top-k";
constexpr int MANDATORY_NUMBER_OF_ARGS = 5; 

ProgramOptions parseArguments(int argc, char* argv[]) {
    if (argc < MANDATORY_NUMBER_OF_ARGS) {
        throw std::runtime_error(ERROR_MESSAGE));
    }
    ProgramOptions options{
        .summaryName = argv[1],
        .inputPath = argv[2],
        .outputPath = argv[3],
        .seed = std::stoull(argv[4])
    };
    for (int i = MANDATORY_NUMBER_OF_ARGS; i < argc; ++i) {
        if (argv[i] == TOP_K_ARGUMENT) {
            options.outputTopK = true;
        }
        else {
            options.summaryArguments.emplace_back(argv[i]);
        }
    }
    return options;
}
