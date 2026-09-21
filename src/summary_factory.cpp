#include "summary_factory.h"
#include "misra_gries.h"
#include <stdexcept>

namespace Exceptions {
    constexpr char MISRA[] = "Misra-Gries expects exactly one parameter: k";
    constexpr char UNKNOWN_SUMMARY = "Unknown summary: {}";
}

namespace Arguments {
    constexpr char MISRA[] = "misra-gries";
}

std::unique_ptr<Summary> createSummary(const ProgramOptions& options) {
    if (options.summaryName == Arguments::MISRA) {
        if (options.summaryArguments.size() != 1) {
            throw std::runtime_error(Exceptions::MISRA);
        }
        const Count k = std::stoull(options.summaryArguments[0]);
        return std::make_unique<MisraGries>(k);
    }

    throw std::runtime_error(Exceptions::UNKNOWN_SUMMARY);
}
