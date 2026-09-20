#ifndef MISRA_GRIES_H
#define MISRA_GRIES_H
#include "sketch.h"
#include <string>
#include <unordered_map>

constexpr int MISRA_NUMBER_OF_ARGUMENTS = 5;

class MisraGries : public Sketch {
public:
    MisraGries(const countType k, std::string& inputFilePath, const std::string& outputFilePath);
    size_t size() override;
private:
    countType k;
    std::unordered_map<keyType, countType> counter;
    void runSketch() override;
    void update(keyType val);
    counterType storeCountsToCounter() override;
};
#endif
