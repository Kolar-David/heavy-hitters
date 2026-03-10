#ifndef MISRA_GRIES_H
#define MISRA_GRIES_H
#include "sketch.h"
#include <string>
#include <unordered_map>

constexpr int MISRA_NUMBER_OF_ARGUMENTS = 3;

class MisraGries : public Sketch {
public:
    MisraGries(countType k, std::string& inputFilePath, std::string& outputFilePath);
    size_t size() override;
    void saveOutputToFile() override;
private:
    countType k;
    std::unordered_map<keyType, countType> counter;
    void runSketch() override;
    void update(countType val);
};
#endif
