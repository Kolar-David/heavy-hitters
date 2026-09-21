#include "runner.h"

#include <utility>

RunResult Runner::run(Summary& summary, const std::vector<Key>& input) const {
    // Update phase.
    const auto updateStart = std::chrono::steady_clock::now();
    for (const Key key : input) {
        summary.update(key);
    }
    const auto updateEnd = std::chrono::steady_clock::now();
    const std::size_t memoryUsage = summary.memoryUsage();


    // Query phase
    std::vector<Estimate> estimates;
    estimates.reserve(input.size());
    const auto queryStart = std::chrono::steady_clock::now();
    for (const Key key : input) {
        estimates.push_back({key, summary.query(key)});
    }
    const auto queryEnd = std::chrono::steady_clock::now();

    return {
        .updateTime = std::chrono::duration_cast<std::chrono::nanoseconds>(updateEnd - updateStart),
        .queryTime = std::chrono::duration_cast<std::chrono::nanoseconds>(queryEnd - queryStart),
        .memoryUsage = memoryUsage,
        .estimates = std::move(estimates)
    };
}
