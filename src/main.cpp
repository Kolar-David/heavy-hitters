#include "arguments.h"
#include "io.h"
#include "runner.h"
#include "summary_factory.h"
#include <exception>
#include <iostream>

int main(int argc, char* argv[]) {
    try {
        const ProgramOptions options = parseArguments(argc, argv);
        const std::vector<Key> input = loadInput(options.inputPath);
        std::unique_ptr<Summary> summary = createSummary(options);
        Runner runner;
        const RunResult result = runner.run(*summary, input);
        writeEstimates(result.estimates, options.outputPath);
        printStatistics(result);
        return 0;
    }
    catch (const std::exception& exception) {
        std::cerr << exception.what() << '\n';
        return 1;
    }
}
