#include "top_k_summary.h"
#include <stdexcept>

namespace Exceptions {
    constexpr char K_POSITIVE[] = "k must be positive";
    constexpr char K_NOT_SET[] = "k has not been set";
}

void TopKSummary::setK(std::size_t value) {
    if (value == 0) {
        throw std::invalid_argument(Exceptions::K_POSITIVE);
    }
    checkK(value);
    _k = value;
}

std::size_t TopKSummary::getK() const {
    if (!_k) {
        throw std::logic_error(Exceptions::K_NOT_SET);
    }
    return *_k;
}
