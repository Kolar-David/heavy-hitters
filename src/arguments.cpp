#include "arguments.h"
#include <stdexcept>

namespace Arguments {
    constexpr char TOP_K[] = "--top-k";
}

namespace Exceptions {
    constexpr char ERROR_MESSAGE[] = "Usage: summary-runner <summary> <input> <output> <seed> [summary parameters...] [--top-k <k>]";
    constexpr char MISSING_TOP_K[] = "--top-k expects a value";
}

constexpr int MANDATORY_NUMBER_OF_ARGS = 5;

ProgramOptions parseArguments(int argc, char* argv[]) {
    if (argc < MANDATORY_NUMBER_OF_ARGS) {
        throw std::runtime_error(Exceptions::ERROR_MESSAGE);
    }
    ProgramOptions options{
        .summaryName = argv[1],
        .inputPath = argv[2],
        .outputPath = argv[3],
        .seed = std::stoull(argv[4]),
        .topK = std::nullopt
    };
    for (int i = MANDATORY_NUMBER_OF_ARGS; i < argc; ++i) {
        const std::string_view argument = argv[i];
        if (argument == Arguments::TOP_K) {
            if (i + 1 >= argc) {
                throw std::runtime_error(Exceptions::MISSING_TOP_K);
            }
            options.topK = std::stoull(argv[++i]);
        }
        else {
            options.summaryArguments.emplace_back(argv[i]);
        }
    }
    return options;
}
