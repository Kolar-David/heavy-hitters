#ifndef RUNNER_H
#define RUNNER_H

#include "summary.h"
#include <chrono>
#include <cstddef>
#include <vector>

struct Estimate {
    Key key;
    Count estimate;
};

struct RunResult {
    std::chrono::nanoseconds updateTime;
    std::chrono::nanoseconds queryTime;
    std::size_t memoryUsage;
    std::vector<Estimate> estimates;
};

class Runner {
public:
    RunResult run(Summary& summary, const std::vector<Key>& input) const;
};

#endif
