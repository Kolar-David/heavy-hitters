#ifndef MISRA_GRIES_H
#define MISRA_GRIES_H
#include "../top_k_summary.h"
#include <cstddef>
#include <unordered_map>
#include <vector>

class MisraGries : public TopKSummary {
public:
    MisraGries(std::size_t capacity);
    void update(Key key) override;
    Count query(Key key) const override;
    std::size_t memoryUsage() const override;
    std::vector<Estimate> topK() const override;
private:
    const std::size_t capacity;
    std::unordered_map<Key, Count> counters;
    void checkK(std::size_t value) const override;
};


#endif
