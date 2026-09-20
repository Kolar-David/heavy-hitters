#ifndef SUMMARY_H
#define SUMMARY_H

#include <cstddef>
#include <cstdint>

using Key = std::uint64_t;
using Count = std::uint64_t;

class Summary {
public:
    virtual ~Summary() = default;
    virtual void update(Key key) = 0;
    virtual Count query(Key key) const = 0;
    virtual std::size_t memoryUsage() const = 0;
};

#endif
