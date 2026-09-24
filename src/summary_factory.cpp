#include "summary_factory.h"
#include "summaries/misra-gries.h"
#include <format>
#include <stdexcept>

namespace Exceptions {
    constexpr char MISRA[] = "Misra-Gries expects exactly one parameter: capacity";
    constexpr char UNKNOWN_SUMMARY[] = "Unknown summary: {}";
}

namespace Arguments {
    constexpr char MISRA[] = "misra-gries";
}

std::unique_ptr<Summary> createSummary(const ProgramOptions& options) {
    if (options.summaryName == Arguments::MISRA) {
        if (options.summaryArguments.size() != 1) {
            throw std::runtime_error(Exceptions::MISRA);
        }
        const std::size_t capacity = std::stoull(options.summaryArguments[0]);
        return std::make_unique<MisraGries>(capacity);
    }

    throw std::runtime_error(std::format(Exceptions::UNKNOWN_SUMMARY, options.summaryName));
}
