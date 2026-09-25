#ifndef SPACE_SAVING_H
#define SPACE_SAVING_H
#include "../top_k_summary.h"
#include <vector>
#include <cstddef>
#include <unordered_map>

class SpaceSaving : public TopKSummary {
public:
    SpaceSaving(std::size_t capacity);
    void update(Key key) override;
    Count query(Key key) const override;
    std::size_t memoryUsage() const override;
    std::vector<Estimate> topK() const override;

private:
    void removeExpiredMinimumItems();
    void rebuildMinimumItems();
    void updateMinimum();
    void checkK(std::size_t value) const override;
    const std::size_t capacity;
    std::unordered_map<Key, Count> counters;
    Count minimum = 0;
    std::vector<Key> minimumItems;
};

#endif
