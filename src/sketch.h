#ifndef SKETCH_H
#define SKETCH_H
#include <cstdint>
#include <string>
#include <iostream>
#include <vector>

using countType = uint64_t;
using keyType = uint64_t;

using counterType = std::vector<countType>;

struct Counter {
    countType counter;
    keyType key;
};

class Sketch {
public:
    Sketch(std::string& inputFilePath, std::string& outputFilePath): inputFilePath(inputFilePath), outputFilePath(outputFilePath) {};
    virtual size_t size() = 0;
    void run();
    void returnTimeOfExecution() = 0;
    counterType storeCountsToCounter() = 0;
    void loadInputFromFile();

protected:
    std::string inputFilePath;
    std::string outputFilePath;
    std::vector<keyType> input;
    void storeCountsToFile();
    virtual void runSketch() = 0;

};
#endif