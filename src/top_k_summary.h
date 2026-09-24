#ifndef TOP_K_SUMMARY_H
#define TOP_K_SUMMARY_H
#include "summary.h"
#include <cstddef>
#include <optional>
#include <vector>


class TopKSummary : public Summary {
public:
    void setK(std::size_t value);
    virtual std::vector<Estimate> topK() const = 0;
protected:
    std::size_t getK() const;
    virtual void checkK(std::size_t value) const = 0;
private:
    std::optional<std::size_t> _k;
};

#endif
