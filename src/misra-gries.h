#ifndef MISRA_GRIES_H
#define MISRA_GRIES_H
#include "sketch.h"
#include <string>
#include <unordered_map>

class MisraGries : public Sketch {
public:
    MisraGries(countType k, std::string& inputFilePath, std::string& outputFilePath);
    size_t size() override;
    void runSketch() override;
    void saveOutputToFile() override;
private:
    countType k;
    std::unordered_map<keyType, countType> counter;
    void update(countType val);
};
#endif
