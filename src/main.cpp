#include "arguments.h"
#include "io.h"
#include "runner.h"
#include "summary_factory.h"
#include "top_k_summary.h"
#include <exception>
#include <iostream>
#include <optional>
#include <stdexcept>

constexpr char SELECTED_SUMMARY_DOES_NOT_SUPPORT_TOP_K[] = "The selected summary does not support top-k output!";

int main(int argc, char* argv[]) {
    try {
        const ProgramOptions options = parseArguments(argc, argv);
        const std::vector<Key> input = loadInput(options.inputPath);
        std::unique_ptr<Summary> summary = createSummary(options);
        TopKSummary* topKSummary = nullptr;
        if (options.topK) {
            topKSummary = dynamic_cast<TopKSummary*>(summary.get());
            if (topKSummary == nullptr) {
                throw std::runtime_error(SELECTED_SUMMARY_DOES_NOT_SUPPORT_TOP_K);
            }
            topKSummary->setK(*options.topK);
        }
        Runner runner;
        const RunResult result = runner.run(*summary, input);
        std::optional<std::vector<Estimate>> topK;
        if (topKSummary != nullptr) {
            topK = topKSummary->topK();
        }
        writeOutput(result.estimates, topK, options.outputPath);
        printStatistics(result);
        return 0;
    }
    catch (const std::exception& exception) {
        std::cerr << exception.what() << '\n';
        return 1;
    }
}
