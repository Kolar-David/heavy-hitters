#ifndef TOP_K_SUMMARY_H
#define TOP_K_SUMMARY_H
#include "summary.h"
#include <cstddef>
#include <vector>


class TopKSummary : public Summary {
public:
    TopKSummary(std::size_t k) : k(k) {}
    virtual std::vector<Estimate> topK() const = 0;
protected:
    std::size_t k;
};

#endif
