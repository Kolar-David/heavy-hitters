#include "misra_gries.h"
#include <algorithm>
#include <stdexcept>
#include <unordered_map>
#include <vector>

namespace Exceptions {
    constexpr char CAPACITY_MUST_BE_POSITIVE[] = "Misra-Gries capacity must be positive!";
    constexpr char CAPACITY_GREATER_TOP_K[] = "Top-k parameter cannot be greater than Misra-Gries capacity!";
}

MisraGries::MisraGries(std::size_t k, std::size_t capacity): TopKSummary(k), _capacity(capacity) {
    if (capacity == 0) {
        throw std::invalid_argument(Exceptions::CAPACITY_MUST_BE_POSITIVE);
    }
    if (k > capacity) {
        throw std::invalid_argument(Exceptions::CAPACITY_GREATER_TOP_K);
    }
}

void MisraGries::update(Key key) {
    auto it = counters.find(key);
    if (it != counters.end()) {
        ++it->second;
        return;
    }
    if (counters.size() < capacity) {
        counters[key] = 1;
        return;
    }
    for (auto& [storedKey, count] : counters) {
        --count;
    }
    std::erase_if(counters, [](const auto& entry) {
        return entry.second == 0;
    });
}

Count MisraGries::query(Key key) const {
    const auto it = counters.find(key);
    if (it == counters.end()) {
        return 0;
    }
    return it->second;
}

std::vector<Estimate> MisraGries::topK() const {
    std::vector<Estimate> estimates;
    estimates.reserve(counters.size());
    for (const auto& [key, count] : counters) {
        estimates.push_back({key, count});
    }
    std::sort(estimates.begin(), estimates.end(),
        [](const Estimate& first, const Estimate& second) {
            return first.estimate > second.estimate;
        }
    );
    if (estimates.size() > k) {
        estimates.resize(k);
    }
    return estimates;
}

std::size_t MisraGries::memoryUsage() const {
    // Probably just temporary
    return sizeof(*this) + counters.size() * sizeof(std::unordered_map<Key, Count>::value_type);
}