#include "space_saving.h"
#include <algorithm>
#include <stdexcept>

namespace Exceptions {
    constexpr char CAPACITY_MUST_BE_POSITIVE[] = "SpaceSaving capacity must be positive!";
    constexpr char TOP_K_GREATER_THAN_CAPACITY[] = "Top-k parameter cannot be greater than SpaceSaving capacity!";
}

SpaceSaving::SpaceSaving(std::size_t capacity): capacity(capacity) {
    if (capacity == 0) {
        throw std::invalid_argument(Exceptions::CAPACITY_MUST_BE_POSITIVE);
    }
}

void SpaceSaving::update(Key key) {
    auto it = counters.find(key);
    if (it != counters.end()) {
        Count oldCount = it->second;
        ++it->second;
        if (counters.size() < capacity) {
            return;
        }
        if (oldCount == minimum) {
            removeExpiredMinimumItems();
            if (minimumItems.empty()) {
                updateMinimum();
            }
        }
        return;
    }

    if (counters.size() < capacity) {
        counters.emplace(key, 1);
        if (counters.size() == capacity) {
            minimum = 1;
            rebuildMinimumItems();
        }
        return;
    }
    removeExpiredMinimumItems();
    Key minimumToReplace = minimumItems.back();
    minimumItems.pop_back();
    counters.erase(minimumToReplace);
    counters.emplace(key, minimum + 1);
    removeExpiredMinimumItems();
    if (minimumItems.empty()) {
        updateMinimum();
    }
}

Count SpaceSaving::query(Key key) const {
    auto it = counters.find(key);
    if (it == counters.end()) {
        return 0;
    }
    return it->second;
}

void SpaceSaving::removeExpiredMinimumItems() {
    while (!minimumItems.empty()) {
        Key key = minimumItems.back();
        auto it = counters.find(key);
        if (it != counters.end() && it->second == minimum) {
            return;
        }
        minimumItems.pop_back();
    }
}

void SpaceSaving::updateMinimum() {
    ++minimum;
    rebuildMinimumItems();
}

void SpaceSaving::rebuildMinimumItems() {
    minimumItems.clear();
    for (const auto& [key, count] : counters) {
        if (count == minimum) {
            minimumItems.push_back(key);
        }
    }
}

std::vector<Estimate> SpaceSaving::topK() const {
    const std::size_t k = getK();
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

std::size_t SpaceSaving::memoryUsage() const {
    return sizeof(*this) + counters.size() * sizeof(std::unordered_map<Key, Count>::value_type) + minimumItems.capacity() * sizeof(Key);
}

void SpaceSaving::checkK(std::size_t value) const {
    if (value > capacity) {
        throw std::invalid_argument(Exceptions::TOP_K_GREATER_THAN_CAPACITY);
    }
}
